#pragma once

#include "./Conf.hpp"
#include <vector>

class Location
{
public:
	Location();
	~Location();
	void set_path(std::string path);
	void set_root(std::string root);
	void set_upload(std::string upload);
	void set_cgi(std::vector<CGI> cgi);
	void set_client_max_body_size(int client_max_body_size);
	void set_allow(allow_methods allow);
	void set_index(std::string index);
	void set_rewrite(std::vector<rew> rewrite);
	void set_error_page(std::vector<error_pages> error_page);
	void set_autoindex(bool autoindex);
	std::string get_path();
	std::string get_root();
	std::string get_upload();
	std::vector<CGI> get_cgi();
	int get_client_max_body_size();
	allow_methods get_allow();
	std::string get_index();
	std::vector<rew> get_rewrite();
	std::vector<error_pages> get_error_page();
	bool get_autoindex();

private:
	std::string 				path;
	std::string 				root;
	std::string 				upload;
	std::vector<CGI> 			cgi;
	int 						client_max_body_size;
	allow_methods 				allow;
	std::string 				index;
	std::vector<rew> 		    rewrite;
	std::vector<error_pages> 	error_page;
	bool 						autoindex;
};