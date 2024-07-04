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
                bool isNewConnection = false, defualtserver=true, newgiro=false;
                do{
                    for (size_t i2 = 0; i2 != webservv.get_n_server(); i2++) {
                        if (servers[i].fd == webservv.servers[i2].get_fd()) {
                            isNewConnection = true;
                            defualtserver = false;
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
                    if(defualtserver==true){
                        servers[i].fd = webservv.servers[0].get_fd();
                        newgiro=true;
                    }
                }while(newgiro==true);
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
						std::string request(buffer, valread);
                        std::string metod=get_metod(request);
                        bool notallow=true;
                        for(size_t i=0;i!=webservv.servers[cli->second].get_lmedallow();i++){
                            if(metod==webservv.servers[cli->second].get_medallow(i))
                                notallow=false;
                        }
                        if(notallow==true){
                            content="<!DOCTYPE html>
                                    <html>
                                        <head>
                                            <meta charset='UTF-8'>
                                            <meta http-equiv='x-ua-compatible' content='ie=8'>
                                            <meta name='keywords' content=''>
                                            <meta name='author' content='Andrei Anghi[Angly colui che regna]'>
                                            <meta name='viewport' content='width=device-width, initial-scale=1'>
                                            <meta name='copyright' content='Andrei Anghi[Angly colui che regna]'>
                                            <title>Error: Metod non allow | Wengly</title>
                                        </head>
                                        <body><h1>Error: Metod non allow</h1></body>
                                    </html>";
                            std::ostringstream convertitore;
                            convertitore << content.size();
                            responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: "+convertitore.str()+"\n\n"+content;
                            continue;
                        }
						std::string ContentType;
						std::string filePath;
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
                        ContentType=getext(filePath);
                        if (content.empty()){
                            filePath=webservv.servers[cli->second].get_error404()
                            content = readFile(filePath);
							if(content.empty()){
                                ContentType="text/html";
                                content="<!DOCTYPE html>
                                        <html>
                                            <head>
                                                <link rel='shortcut icon' href='./Assets/img/icona.jpg' type='image/x-icon'>
                                                <link rel='stylesheet' type='text/css' href='./Assets/main.css'>
                                                <meta charset='UTF-8'>
                                                <meta http-equiv='x-ua-compatible' content='ie=8'>
                                                <meta name='keywords' content=''>
                                                <meta name='author' content='Andrei Anghi[Angly colui che regna]'>
                                                <meta name='viewport' content='width=device-width, initial-scale=1'>
                                                <meta name='copyright' content='Andrei Anghi[Angly colui che regna]'>
                                                <title>No Title | Wengly</title>
                                            </head>
                                            <body>
                                                <center>
                                                    <div class='centro'>
                                                        <h1 class='titolo'>WebServer: Wengly</h1>
                                                        <br>
                                                        <br>";
                                if(webservv.servers[cli->second].get_dir()=="yes"){
                                    content+="<p class='sottotitolo'>File della cartella:";
                                    DIR				*dir;
                                    struct dirent	*entry;

                                    dir = opendir(get_path());
                                    if (dir == NULL){
                                        std::cout<<"Marshal: Opendir error"<<std::endl;
                                        exit(-1);
                                    }
                                    entry = readdir(dir);
                                    while (entry != NULL){
                                        if (entry->d_type == DT_REG){
                                            if (strncmp(entry->d_name, ".", 2) != 0 && strncmp(entry->d_name, "..", 3) != 0)
                                                content+="<p class='sottotitolo'><a class='link' href='"+entry->d_name+"'>"+entry->d_name+"</a></p>";
                                        }
                                        entry = readdir(dir);
                                    }
                                    content+="</p>";
                                }else{
                                    content+="Impostazione showdir: no";
                                }
                                content+="
                                                    </div>
                                                </center>
                                            </body>
                                        </html>";
                            }
						}
						std::ostringstream convertitore;
						convertitore << content.size();
                        responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: "+ContentType+"\nContent-Length: "+convertitore.str()+"\n\n"+content;
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
