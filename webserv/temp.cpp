#include <iostream>
#include <vector>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <poll.h>
#include <fcntl.h>

#define PORT1 8080
#define PORT2 8081
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int set_non_blocking(int socket) {
    int flags = fcntl(socket, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    flags |= O_NONBLOCK;
    if (fcntl(socket, F_SETFL, flags) == -1) {
        perror("fcntl");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int create_and_bind_socket(int port) {
    int sockfd;
    struct sockaddr_in address;
    int opt = 1;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    set_non_blocking(sockfd);

    return sockfd;
}

int main() {
    int server_fd1 = create_and_bind_socket(PORT1);
    int server_fd2 = create_and_bind_socket(PORT2);

    std::vector<struct pollfd> fds;
    fds.push_back({server_fd1, POLLIN, 0});
    fds.push_back({server_fd2, POLLIN, 0});

    std::cout << "Server listening on ports " << PORT1 << " and " << PORT2 << std::endl;

    while (true) {
        int poll_count = poll(fds.data(), fds.size(), -1);

        if (poll_count < 0) {
            perror("poll");
            exit(EXIT_FAILURE);
        }

        for (size_t i = 0; i < fds.size(); ++i) {
            if (fds[i].revents & POLLIN){
                if (fds[i].fd == server_fd1 || fds[i].fd == server_fd2) {
                    // Gestire nuove connessioni
                    int new_socket;
                    struct sockaddr_in address;
                    socklen_t addrlen = sizeof(address);
                    new_socket = accept(fds[i].fd, (struct sockaddr *)&address, &addrlen);

                    if (new_socket < 0) {
                        perror("accept");
                        continue;
                    }
                    set_non_blocking(new_socket);

                    int dest_port = ntohs(address.sin_port);
                    if (dest_port == PORT1) {
                        fds.push_back({new_socket, POLLIN, 0});
                        std::cout << "New connection accepted on port " << PORT1 << std::endl;
                    } else if (dest_port == PORT2) {
                        fds.push_back({new_socket, POLLIN, 0});
                        std::cout << "New connection accepted on port " << PORT2 << std::endl;
                    } else {
                        // Porta non gestita, chiudi la connessione
                        std::cerr << "Connection from unsupported port " << dest_port << ". Closing connection." << std::endl;
                        close(new_socket);
                    }
                } else {
                    // Gestire le comunicazioni con i client esistenti
                    char buffer[BUFFER_SIZE];
                    int valread = read(fds[i].fd, buffer, BUFFER_SIZE);
                    if (valread < 0) {
                        perror("read");
                        close(fds[i].fd);
                        fds.erase(fds.begin() + i);
                        --i;
                    } else if (valread == 0) {
                        // Connessione chiusa
                        std::cout << "Client disconnected" << std::endl;
                        close(fds[i].fd);
                        fds.erase(fds.begin() + i);
                        --i;
                    } else {
                        // Rispondere al client
                        buffer[valread] = '\0';
                        const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world";
                        send(fds[i].fd, hello, strlen(hello), 0);
                        std::cout << "Response sent to client" << std::endl;
                    }
                }
            }
        }
    }

    close(server_fd1);
    close(server_fd2);
    return 0;
}
