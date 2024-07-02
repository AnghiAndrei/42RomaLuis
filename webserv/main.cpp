#include"webserv.hpp"

int main(int argc, char **argv){
	webserv webservv;
	if(check(argc, argv, &webservv)==-1)
		return -1;
	
	std::vector<struct pollfd> servers;
	for (size_t i=0;i!=webservv.get_n_server();i++){
		webservv.servers[i].start();
		struct pollfd pfd;
		pfd.fd = webservv.servers[i].get_fd();
		pfd.events = POLLIN;
		pfd.revents = 0;
    	servers.push_back(pfd);
		std::cout<<"Server listening on port "<<webservv.servers[i].get_port()<<std::endl;
	}

	while(true){
        int poll_count=poll(servers.data(), servers.size(), -1);
        if(poll_count<0){
			std::cout<<"Marshal: Poll failed"<<std::endl;
            exit(-1);
        }
		bool newcon=false;
        for (size_t i = 0; i < servers.size(); ++i){
			if(newcon==true)
				break;
            if (servers[i].revents & POLLIN){
				bool velse=false;
				for(size_t i2=0;i2!=webservv.get_n_server();i2++){
					if(newcon==true)
						break;
					if(servers[i].fd==webservv.servers[i2].get_fd()){
						velse=true;
						int new_socket;
						struct sockaddr_in address;
						socklen_t addrlen = sizeof(address);
						new_socket = accept(servers[i].fd, (struct sockaddr *)&address, &addrlen);
						if(new_socket < 0){
							std::cout<<"[Warning] Accept"<<std::endl;
							continue;
						}
						setnblocking(new_socket);
						bool canc=true;
						for(size_t i2=0;i2!=webservv.get_n_server();i2++){
							if(servers[i].fd==webservv.servers[i2].get_fd()){
								struct pollfd pfd;
								canc=false;
								pfd.fd=new_socket;
								pfd.events=POLLIN;
								pfd.revents=0;
								newcon=true;
								servers.push_back(pfd);
							}
                        	std::cout<<"Nuova connessione nel fd: "<<webservv.servers[i2].get_fd()<<std::endl;
						}
						if(canc==true)
							close(new_socket);
					}
				}
				if(velse==false){
					char buffer[BUFFER_SIZE];
					int valread=read(servers[i].fd, buffer, BUFFER_SIZE);
					if(valread<=0){
						//chiusura
						close(servers[i].fd);
						servers.erase(servers.begin() + i);
						--i;
					}else{
						//risposta
						buffer[valread] = '\0';
						const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 31\n\nVoglio mangiare il tuo pancreas";
						send(servers[i].fd, hello, strlen(hello), 0);
						std::cout<<"Servito fd: "<<servers[i].fd<<std::endl;
					}
				}
            }
        }
    }
	//webservv.print_server();
    return 0;
}