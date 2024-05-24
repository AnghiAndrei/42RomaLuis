#include "Server.hpp"

Server::Server()
{
}

Server::~Server()
{
}

void Server::set_server_name(std::string server_name)
{
	this->server_name = server_name;
}

void Server::set_listen(int listen)
{
	this->listen = listen;
}

void Server::set_root(std::string root)
{
	this->root = root;
}

void Server::set_upload(std::string upload)
{
	this->upload = upload;
}

void Server::set_cgi(std::vector<CGI> cgi)
{
	this->cgi = cgi;
}

void Server::set_client_max_body_size(int client_max_body_size)
{
	this->client_max_body_size = client_max_body_size;
}

void Server::set_allow(allow_methods allow)
{
	this->allow = allow;
}

void Server::set_index(std::string index)
{
	this->index = index;
}

void Server::set_rewrite(std::vector<rew> rewrite)
{
	this->rewrite = rewrite;
}

void Server::set_error_page(std::vector<error_pages> error_page)
{
	this->error_page = error_page;
}

void Server::set_autoindex(bool autoindex)
{
	this->autoindex = autoindex;
}

void Server::set_locations(std::vector<Location> locations)
{
	this->locations = locations;
}

std::string Server::get_server_name()
{
	return this->server_name;
}

int Server::get_listen()
{
	return this->listen;
}

std::string Server::get_root()
{
	return this->root;
}

std::string Server::get_upload()
{
	return this->upload;
}

std::vector<CGI> Server::get_cgi()
{
	return this->cgi;
}

int Server::get_client_max_body_size()
{
	return this->client_max_body_size;
}

allow_methods Server::get_allow()
{
	return this->allow;
}

std::string Server::get_index()
{
	return this->index;
}

std::vector<rew> Server::get_rewrite()
{
	return this->rewrite;
}

std::vector<error_pages> Server::get_error_page()
{
	return this->error_page;
}

bool Server::get_autoindex()
{
	return this->autoindex;
}

std::vector<Location> Server::get_locations()
{
	return this->locations;
}

void Server::set_cgi_bin(std::string cgi_bin)
{
	this->cgi_bin = cgi_bin;
}

std::string Server::get_cgi_bin()
{
	return this->cgi_bin;
}

Server Server::select_server(std::vector<Server> servers, int port)
{
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it)
	{
		if (it->get_listen() == port)
			return *it;
	}
	return Server();
}