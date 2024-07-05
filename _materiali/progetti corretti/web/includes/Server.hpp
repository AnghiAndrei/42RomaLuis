#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#include "Location.hpp"

class Server
{
public:
	int client_body_limit;
	bool autoindex;
	std::string root;
	std::string server_name;
	std::vector<std::string> index;
	std::vector<MethodType> allow_methods;
	std::map<int, std::string> error_pages;
	
	std::vector<Location> locations;
	
	int redirect_status;
	std::string redirect_url;

	struct timeval send_timeout;
	struct timeval recv_timeout;

public:
	std::string host;
	std::string port;
	
	int listen_socket;
	
	Server();
	~Server();

	void create_socket();
	void print_server_info();

	static MethodType s_to_methodtype(std::string str);

	Location* get_cur_location(std::string request_uri) const;
	bool is_in_location(std::string location_path, std::string request_uri) const;
};

#endif