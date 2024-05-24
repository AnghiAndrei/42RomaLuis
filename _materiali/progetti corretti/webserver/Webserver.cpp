#include "Webserver.hpp"
void close_socket(int client_sock, std::map<std::string, std::string> request_map)
{
	if (request_map.find("Connection") != request_map.end())
	{
		if (request_map["Connection"].find("close") != std::string::npos)
			close(client_sock);
	}
   
}

void handle_client(int client_socket, std::vector<Server> servers) {
    
    std::vector<char> message = Request_manager::recive_request(client_socket);

    std::string message_string(message.begin(), message.end());

    std::map<std::string, std::string> request_map = Request_manager::parse_request(message_string);

    Server server = Server::select_server(servers, atoi(request_map["port"].c_str()));

    //se request map contiene Content-Length, allora content_length = atoi(request_map["Content-Length"].c_str())
    int content_length = 0;
    if (request_map.find("Content-Length") != request_map.end())
        content_length = atoi(request_map["Content-Length"].c_str());

    Location location = Request_manager::select_location(server, request_map["path"]);
    
    int max_body_size = Request_manager::search_max_body_size(server, request_map, location);
    
    if (content_length > max_body_size) {
        Error_page::send_error_page(server, "/", client_socket, 413, "Request Entity Too Large", location);
        return;
    }

    std::vector<char> message_body;

    if (content_length > 0) {
        message_body = Request_manager::get_request_body(client_socket, content_length);
    }

   /* if (server.get_server_name() != request_map["host"]) {
        Error_page::send_error_page(server, "/", client_socket, 403, "Forbidden", location);
        return;
    }*/
    
    if (request_map["request"] == "GET") {
        Get_request::get_response(client_socket, server, request_map, location);
        close_socket(client_socket, request_map);
        return;
    } else if (request_map["request"] == "POST") {
        Post_request::post_response(client_socket, server, request_map, message_body, location);
        close_socket(client_socket, request_map);
        return;
    } else if (request_map["request"] == "DELETE") {
        Delete_request::delete_response(client_socket, server, request_map, location);
        close_socket(client_socket, request_map);
        return;
    } else {
        Error_page::send_error_page(server, "/", client_socket, 501, "Not Implemented", location);
        close_socket(client_socket, request_map);
        return;
    }

    return;
}

int Webserver::run(std::vector<Server> servers) {
    std::vector<int> ports;

    for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it) {
        ports.push_back(it->get_listen());
    }

    std::vector<int> server_sockets;
    struct pollfd *fds = new struct pollfd[ports.size()];
    int num_fds = 0;

    for (std::vector<int>::const_iterator it = ports.begin(); it != ports.end(); ++it) {
        // Crea il socket del server
        int server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket < 0) {
            std::cerr << "Error opening socket" << std::endl;
            delete[] fds;
            return -1;
        }

        // Configura l'indirizzo del server
        struct sockaddr_in server_address;
        std::memset(&server_address, 0, sizeof(server_address));
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(*it);

        // Lega il socket all'indirizzo del server
        if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
            std::cerr << "Error binding socket" << std::endl;
            close(server_socket);
            delete[] fds;
            return -1;
        }

        // Metti il socket del server in ascolto
        if (listen(server_socket, 5) < 0) {
            std::cerr << "Error listening on socket" << std::endl;
            close(server_socket);
            delete[] fds;
            return -1;
        }

        std::cout << "Server listening on port " << *it << std::endl;
        server_sockets.push_back(server_socket);

        // Aggiungi il socket alla lista di quelli monitorati da poll
        fds[num_fds].fd = server_socket;
        fds[num_fds].events = POLLIN;
        num_fds++;
    }

    while (true) {
        int activity = poll(fds, num_fds, -1);
        if (activity < 0) {
            std::cerr << "Error in poll" << std::endl;
            delete[] fds;
            return -1;
        }

        for (int i = 0; i < num_fds; ++i) {
            if (fds[i].revents & POLLIN) {
                struct sockaddr_in client_address;
                socklen_t client_address_size = sizeof(client_address);
                int client_socket = accept(fds[i].fd, (struct sockaddr *)&client_address, &client_address_size);

                if (client_socket < 0) {
                    std::cerr << "Error accepting connection" << std::endl;
                    continue;
                }
                handle_client(client_socket, servers);

            }
        }
    }

    delete[] fds;
    return 0;
}
