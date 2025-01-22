#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct s_client{
	int id;
	char msg[1000000];
} t_client;

t_client client[2048];

fd_set current, readfd, writefd;
int serverfd, maxfd=0, gfd=0;
char send_msg[1000000], recive_msg[1000000];

void send_all(int excludi, int server){
	for(int i=0; i != maxfd; i++){
		if(i!=server && FD_ISSET(i, &writefd) && i != excludi)
			if(send(i, send_msg, strlen(send_msg), 0) == -1){
				write(2, "Fatal error\n", 12);
				exit(1);
			}
	}
}

int main(int ac, char **av){
	if (ac != 2){
		write(2, "Wrong number of arguments\n", 26);
		exit(1);
	}

	struct sockaddr_in serveraddress;
	socklen_t len = sizeof(struct sockaddr_in);
	serverfd = socket(AF_INET, SOCK_STREAM, 0);
	if(serverfd == -1){
		write(2, "Fatal error\n", 12);
		exit(1);
	}
	maxfd = serverfd;

	FD_ZERO(&current);
	FD_SET(serverfd, &current);
	bzero(client, sizeof(client));
	bzero(&serveraddress, sizeof(serveraddress));

	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = htonl(2130706433);
	serveraddress.sin_port = htons(atoi(av[1]));

	if(bind(serverfd, (const struct sockaddr *)&serveraddress, sizeof(serveraddress)) == -1 || listen(serverfd, 100) == -1){
		write(2, "Fatal error\n", 12);
		exit(1);
	}

	while(1){
		readfd = writefd = current;
		if(select(maxfd + 1, &readfd, &writefd, 0, 0) == -1) continue;
		for (int fd = 0; fd <= maxfd; fd++){
			if(FD_ISSET(fd, &readfd)){
				if(fd == serverfd){
					int clientfd = accept(serverfd, (struct sockaddr *)&serveraddress, &len);
					if(clientfd == -1) continue;
					if(clientfd > maxfd) maxfd = clientfd;
					client[clientfd].id  = gfd++;
					FD_SET(clientfd, &current);
					sprintf(send_msg, "server: client %d just arrived\n", client[clientfd].id);
					send_all(clientfd, serverfd);
					break;
				}else{
					int  ret = recv(fd, recive_msg, sizeof(recive_msg), 0);
					if(ret == -1) continue;
					else if(ret == 0){
						sprintf(send_msg, "server: client %d just left\n", client[fd].id);
						send_all(fd, serverfd);
						FD_CLR(fd, &current);
						close(fd);
						bzero(client[fd].msg, strlen(client[fd].msg));
						break;
					}else{
						for (int i=0, j=strlen(client[fd].msg); i!=ret; i++, j++){
							client[fd].msg[j] = recive_msg[i];
							if(client[fd].msg[j] == '\n'){
								client[fd].msg[j] = '\0';
								sprintf(send_msg, "client %d: %s\n", client[fd].id, client[fd].msg);
								send_all(fd, serverfd);
								bzero(client[fd].msg, strlen(client[fd].msg));
								j = -1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

//compila con: gcc -Werror -Wall -Werror *.c
//avvia: ./a.out 8081
//collegati con 2 terminali facendo: nc 127.0.0.1 8081