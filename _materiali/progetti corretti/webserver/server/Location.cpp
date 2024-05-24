#include "Location.hpp"

void Location::set_path(std::string path)
{
	this->path = path;
}

void Location::set_root(std::string root)
{
	this->root = root;
}

void Location::set_upload(std::string upload)
{
	this->upload = upload;
}

void Location::set_cgi(std::vector<CGI> cgi)
{
	this->cgi = cgi;
}

void Location::set_client_max_body_size(int client_max_body_size)
{
	this->client_max_body_size = client_max_body_size;
}

void Location::set_allow(allow_methods allow)
{
	this->allow = allow;
}

void Location::set_index(std::string index)
{
	this->index = index;
}

void Location::set_rewrite(std::vector<rew> rewrite)
{
	this->rewrite = rewrite;
}

void Location::set_error_page(std::vector<error_pages> error_page)
{
	this->error_page = error_page;
}

void Location::set_autoindex(bool autoindex)
{
	this->autoindex = autoindex;
}

std::string Location::get_path()
{
	return this->path;
}

std::string Location::get_root()
{
	return this->root;
}	

std::string Location::get_upload()
{
	return this->upload;
}	

std::vector<CGI> Location::get_cgi()
{
	return this->cgi;
}	

int Location::get_client_max_body_size()
{
	return this->client_max_body_size;
}	

allow_methods Location::get_allow()
{
	return this->allow;
}	

std::string Location::get_index()
{
	return this->index;
}	

std::vector<rew> Location::get_rewrite()
{
	return this->rewrite;
}		

std::vector<error_pages> Location::get_error_page()
{
	return this->error_page;
}	

bool Location::get_autoindex()
{
	return this->autoindex;
}

Location::Location()
{
	this->path = "";
	this->root = "";
	this->upload = "";
	this->cgi = std::vector<CGI>();
	this->client_max_body_size = 0;
	this->allow.GET = false;
	this->allow.POST = false;
	this->allow.DELETE = false;
	this->index = "";
	this->rewrite = std::vector<rew>();
	this->error_page = std::vector<error_pages>();
	this->autoindex = false;
}

Location::~Location()
{
}
