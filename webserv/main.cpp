#include "webserv.hpp"

int main(int argc, char **argv, char **env){
    webserv webservv;
    if (check(argc, argv, &webservv) == -1)
        return -1;

    std::vector<struct pollfd> servers;
	std::map<int, int> client_to_server; //fd client->fd server
    std::map<int, std::string> responses; //fd->risposta

    for (size_t i = 0; i != webservv.get_n_server(); i++) {
        webservv.servers[i].start();
        struct pollfd pfd;
        pfd.fd = webservv.servers[i].get_fd();
        pfd.events = POLLIN;
        pfd.revents = 0;
        servers.push_back(pfd);
        std::cout << "Server listening on port " << webservv.servers[i].get_port() << std::endl;
    }

    while (true) {
        int poll_count = poll(servers.data(), servers.size(), -1);
        if (poll_count < 0) {
            std::cout << "Marshal: Poll failed" << std::endl;
            exit(-1);
        }
        for (size_t i = 0; i < servers.size(); ++i) {
            if (servers[i].revents & POLLIN) {
                bool isNewConnection = false;
                for (size_t i2 = 0; i2 != webservv.get_n_server(); i2++) {
                    if (servers[i].fd == webservv.servers[i2].get_fd()) {
                        isNewConnection = true;
                        int new_socket;
                        struct sockaddr_in address;
                        socklen_t addrlen = sizeof(address);
                        new_socket = accept(servers[i].fd, (struct sockaddr *)&address, &addrlen);
                        if (new_socket < 0) {
                            std::cout << "[Warning] Accept" << std::endl;
                            continue;
                        }
                        setnblocking(new_socket);
                        struct pollfd pfd;
                        pfd.fd = new_socket;
                        pfd.events = POLLIN | POLLOUT;
                        pfd.revents = 0;
                        servers.push_back(pfd);
						client_to_server[new_socket] = i2;
                        std::cout << "Nuova connessione nel fd: " << webservv.servers[i2].get_fd() << std::endl;
                    }
                }
                if (!isNewConnection) {
                    char buffer[BUFFER_SIZE];
                    int valread = read(servers[i].fd, buffer, BUFFER_SIZE);
                    if (valread <= 0) {
                        // chiusura
                        std::cout << "chiuso fd: " << servers[i].fd << std::endl;
                        close(servers[i].fd);
						client_to_server.erase(servers[i].fd);
                        servers.erase(servers.begin() + i);
                        --i;
                    }else{
						std::map<int, int>::iterator cli = client_to_server.find(servers[i].fd);
						std::string filePath;
						std::string request(buffer, valread);
                        std::string url = parseRequest(request);
                        if(url == "/")
                            filePath = webservv.servers[cli->second].get_root() + webservv.servers[cli->second].get_index();
                        else
                            filePath = webservv.servers[cli->second].get_root() + url;

                        std::string content;
						if(endsWith(filePath, ".php"))
                            content = executePHP(filePath, env);
                        else
                            content = readFile(filePath);
                        if (content.empty()){
                            content = readFile(webservv.servers[cli->second].get_error404());
							if(content.empty())
								content = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 9\n\nNot Found";
						}
						std::ostringstream convertitore;
						convertitore << content.size();
                        responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: "+getext(filePath)+"\nContent-Length: "+convertitore.str()+"\n\n"+content;
                    }
                }
            }else if (servers[i].revents & POLLOUT){
                std::map<int, std::string>::iterator it = responses.find(servers[i].fd);
                if (it != responses.end()){
                    send(servers[i].fd, it->second.c_str(), it->second.size(), 0);
                    std::cout << "Servito fd: " << servers[i].fd << std::endl;
                    responses.erase(it);
                }
            }
        }
    }
    return 0;
}
