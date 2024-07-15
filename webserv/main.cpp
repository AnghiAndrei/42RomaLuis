#include "webserv.hpp"

int main(int argc, char **argv, char **env){
    webserv webservv;
    if (check(argc, argv, &webservv) == -1)
        return -1;

    std::vector<struct pollfd> servers;
	std::map<int, int> client_to_server; //fd client->fd server
    std::map<int, std::string> responses; //fd->risposta
    std::map<int, std::string> post_save; //fd->post

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
        for (size_t i = 0; i < servers.size(); ++i){
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
                if (!isNewConnection){
					std::request="";
                    ssize_t bytesRead;
					char buffer[BUFFER_SIZE2];
					while ((bytesRead = read(servers[i].fd, buffer, BUFFER_SIZE2)) > 0 || (request.size()>=2 && request[request.size()-1]=='\r' && request[request.size()]=='\n')){
						request.append(buffer, bytesRead);
					}

					std::string query_post="";
					std::map<int, std::string>::iterator postit = post_save.find(servers[i].fd);
					if (postit !=post_save.end()){
						query_post=post_save[postit->first];
					}
					t_master ris;
					std::map<int, int>::iterator cli = client_to_server.find(servers[i].fd);
					std::string ContentType;
					std::string filePath;
					std::istringstream requestStream(request);
					std::string metod, url, protocol;
					requestStream >> metod >> url >> protocol;
					if(protocol==""){;}
					size_t pos = url.find('?');
					std::string query_get="";
					if(pos<=url.size())
						query_get = url.substr(pos+1, url.size());
					url = url.substr(0, pos);
					std::string content;
					std::string numeri="";
					size_t posCL=request.find("Content-Length: ");
					if(posCL+16<request.size()){
						for (size_t i=posCL+16; isdigit(request[i]);i++)
							numeri+=request[i];
					}else
						numeri="0";
					unsigned long long int ContentLength=stoull(numeri.c_str());
					if(ContentLength>stoull(webservv.servers[cli->second].get_body_size().c_str())){
						filePath=webservv.servers[cli->second].get_error413();
						ContentType=getext(filePath);
						ris = leggi_file(filePath, servers[i].fd, webservv.servers[cli->second], env, query_get, query_post);
						content = ris.content;
						std::ostringstream convertitore2;
						convertitore2 << content.size();
						responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: "+ContentType+"\nContent-Length: "+convertitore2.str()+"\n\n"+content;
						std::cout<<"Risposta per: "<<servers[i].fd<<"; con: "<<filePath<<std::endl;
						continue;
					}

					if(webservv.servers[cli->second].get_lridirect()==2){
						if (url == webservv.servers[cli->second].get_ridirect(0)) {
							std::string newLocation=webservv.servers[cli->second].get_ridirect(1);
							responses[servers[i].fd]="HTTP/1.1 301 Moved Permanently\nLocation: "+newLocation+"\n\n";
							std::cout<<"Risposta per: "<<servers[i].fd<<"; con: REDIRECT"<<std::endl;
							continue;
						}
					}

					if(metod=="DELETE"){
						responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: 16\n\nRichiesta DELETE";
						std::cout<<"Risposta per: "<<servers[i].fd<<"; con: DELETE"<<std::endl;
					}else if(metod=="GET" || metod=="POST"){
						if(metod=="POST"){
							if(request.find("multipart/form-data") != std::string::npos){
								bytesRead = read(servers[i].fd, buffer, BUFFER_SIZE2);
								request.append(buffer, bytesRead);
								while ((bytesRead = read(servers[i].fd, buffer, BUFFER_SIZE2)) > 0 || (request.size()>=2 && request[request.size()-1]=='\r' && request[request.size()]=='\n')){
									request.append(buffer, bytesRead);
								}

								std::string fileout="";
								size_t posfilename = request.find("filename=");
								if (posfilename != std::string::npos){
									posfilename += 10;
									while(request[posfilename]!='"'){
										fileout+=request[posfilename];
										if(fileout[fileout.size()]==' ')
											fileout.replace(posfilename, 1, "%20");
										posfilename++;
									}
								}
								if (fileout.empty()){
									filePath=webservv.servers[cli->second].get_error500();
									ContentType=getext(filePath);
									ris = leggi_file(filePath, servers[i].fd, webservv.servers[cli->second], env, query_get, query_post);
									content = ris.content;
									std::ostringstream convertitore3;
									convertitore3 << content.size();
									responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: "+ContentType+"\nContent-Length: "+convertitore3.str()+"\n\n"+content;
									std::cout<<"Risposta per: "<<servers[i].fd<<"; con: "<<filePath<<std::endl;
									continue;
								}
								std::ofstream file_out(webservv.servers[cli->second].get_root_assets+"/"+fileout, std::ios::binary);
								if (!file_out.is_open()){
									filePath=webservv.servers[cli->second].get_error500();
									ContentType=getext(filePath);
									ris = leggi_file(filePath, servers[i].fd, webservv.servers[cli->second], env, query_get, query_post);
									content = ris.content;
									std::ostringstream convertitore3;
									convertitore3 << content.size();
									responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: "+ContentType+"\nContent-Length: "+convertitore3.str()+"\n\n"+content;
									std::cout<<"Risposta per: "<<servers[i].fd<<"; con: "<<filePath<<std::endl;
									continue;
								}
								for (size_t i = 0; i < ContentLength; i++){
									bytesRead = read(servers[i].fd, buffer, BUFFER_SIZE2);
									file_out.write(buffer, 1);
								}
								file_out.close();
							}else{
								char buffer2[BUFFER_SIZE];
								while ((bytesRead = read(servers[i].fd, buffer2, BUFFER_SIZE)) > 0){
									request.append(buffer2, bytesRead);
								}
								posCL=request.find("\r\n\r\n");
								if(posCL+4<request.size()){
									query_post="";
									size_t i2=0;
									for (size_t i=posCL+4;i2!=ContentLength;i++){
										query_post+=request[i];
										i2++;
									}
									post_save[servers[i].fd]=query_post;
								}
							}
						}
						if(url == "/")
							filePath = webservv.servers[cli->second].get_root() + webservv.servers[cli->second].get_index();
						else
							filePath = webservv.servers[cli->second].get_root() + url;
						if (!fileExists(filePath.c_str())){
							filePath=webservv.servers[cli->second].get_error404();
							ContentType=getext(filePath);
							ris = leggi_file(filePath, servers[i].fd, webservv.servers[cli->second], env, query_get, query_post);
							content = ris.content;
						}
						if(filePath[filePath.size()-1]=='/' && dirExists(filePath)==false && !fileExists(webservv.servers[cli->second].get_error404().c_str())){
							filePath=webservv.servers[cli->second].get_error404();
							ContentType=getext(filePath);
							ris = leggi_file(filePath, servers[i].fd, webservv.servers[cli->second], env, query_get, query_post);
							content = ris.content;
							std::ostringstream convertitore2;
							convertitore2 << content.size();
							responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: "+ContentType+"\nContent-Length: "+convertitore2.str()+"\n\n"+content;
							std::cout<<"Risposta per: "<<servers[i].fd<<"; con: "<<filePath<<std::endl;
							continue;
						}
						if(filePath[filePath.size()-1]=='/'){
							filePath+=webservv.servers[cli->second].get_index();
						}
						if(!fileExists(filePath.c_str())){
							ContentType="text/html";
							content="<!DOCTYPE html><html><head><link rel='shortcut icon' href='./Assets/img/icona.jpg' type='image/x-icon'><style>*{text-decoration: none;color: rgb(255, 135, 211);}html{background-color:rgb(255, 211, 239);background-color: pink;height: 100vh;width: 100vw;margin: 0;padding: 0;}body{height: 100%;width: 100%;margin: 0;padding: 0;position: fixed;top: 0;}.centro,.centro2{background-color: white;border: 2px solid rgb(255, 129, 190);border-radius: 3%;margin-top: 5vh;padding: 30px;}.centro{width: 500px;}.centro2{width: 800px;}.sottotitolo, .sottotitolod{font-size: 25px;}.sottotitolod{text-align: left;}.titolo{font-size: 30px;}.link{text-decoration: underline;}.pulsanti{background-color: rgb(255, 184, 217);color: white;font-size: 20px;border: 2px solid rgb(255, 129, 190);border-radius: 3%;}.img{width: auto;height: 200px;}.linea{border: rgb(255, 135, 211) 1px solid;width: 80%;}</style><meta charset='UTF-8'><meta http-equiv='x-ua-compatible' content='ie=8'><meta name='keywords' content=''><meta name='author' content='Andrei Anghi[Angly colui che regna]'><meta name='viewport' content='width=device-width, initial-scale=1'><meta name='copyright' content='Andrei Anghi[Angly colui che regna]'><title>Nessun titolo | Wengly</title></head><body><center><div class='centro'><h1 class='titolo'>WebServer: Wengly</h1><br><br>";
							if(webservv.servers[cli->second].get_showdir()=="yes"){
								content+="<p class='sottotitolo'>File della cartella:";
								DIR				*dir;
								struct dirent	*entry;
								std::cout<<getAbsolutePath(GetRootPath()+url, 0).c_str()<<std::endl;
								dir=opendir(getAbsolutePath(GetRootPath()+url, 0).c_str());
								if (dir == NULL){
									content+="<p class='sottotitolo'>Marshal: Errore in opendir</p></div></center></body></html>";										
								}else{
									entry = readdir(dir);
									while (entry != NULL){
										if (entry->d_type == DT_REG){
											std::string temp=entry->d_name;
											content+=("<p class='sottotitolo'><a class='link' href='"+temp+"'>"+temp+"</a></p>").c_str();
										}
										entry = readdir(dir);
									}
									closedir(dir);
									content+="</p>";
								}
							}else
								content+="Impostazione showdir: no";
							content+="</div></center></body></html>";
						}else{
							ContentType=getext(filePath);
							ris = leggi_file(filePath, servers[i].fd, webservv.servers[cli->second], env, query_get, query_post);
							content = ris.content;
						}
						std::ostringstream convertitore;
						convertitore << content.size();
						responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: "+ContentType+"\nContent-Length: "+convertitore.str()+"\n\n"+content;
						std::cout<<"Risposta per: "<<servers[i].fd<<"; con: "<<filePath<<std::endl;
					}else{
						filePath=webservv.servers[cli->second].get_error405();
						ContentType=getext(filePath);
						ris = leggi_file(filePath, servers[i].fd, webservv.servers[cli->second], env, query_get, query_post);
						content = ris.content;
						std::ostringstream convertitore2;
						convertitore2 << content.size();
						responses[servers[i].fd]="HTTP/1.1 200 OK\nContent-Type: "+ContentType+"\nContent-Length: "+convertitore2.str()+"\n\n"+content;
						std::cout<<"Risposta per: "<<servers[i].fd<<"; con: "<<filePath<<std::endl;
					}
				}
            }else if (servers[i].revents & POLLOUT){
                std::map<int, std::string>::iterator it = responses.find(servers[i].fd);
                if (it != responses.end()){
                    send(servers[i].fd, it->second.c_str(), (it->second.size()+1), 0);
                    responses.erase(it);

					// std::map<int, std::string>::iterator postit2 = post_save.find(servers[i].fd);
					// if (postit2 !=post_save.end())
					// 	post_save.erase(postit2);
					std::cout << "chiuso fd: " << servers[i].fd << std::endl;
                    close(servers[i].fd);
					client_to_server.erase(servers[i].fd);
                    servers.erase(servers.begin() + i);
                    --i;
                }
            }
        }
    }
    return 0;
}