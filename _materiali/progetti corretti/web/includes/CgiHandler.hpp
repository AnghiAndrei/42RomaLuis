#ifndef CGIHANDLER_HPP
#define CGIHANDLER_HPP

#include <unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 
#include <signal.h>
#include "Utils.hpp"
#include "Request.hpp"
#include "Location.hpp"


#define BUFFER_SIZE 100

class CgiHandler
{
	private:
		std::map<std::string, std::string> env;
		FILE *resource_p;
		std::string file_resource;
		int pipe_wfd;
		int pipe_rfd;

	public:
		CgiHandler(Request &request, Location& loc);
		char** set_env();
		int excute_CGI(Request &Request, Location &loc);

		friend std::ostream &operator<<(std::ostream &out, CgiHandler &ch)
		{
			out << "cgi_env\n"; 
			for (std::map<std::string, std::string>::iterator it = ch.env.begin(); it != ch.env.end(); it++)
			{
				out << "first : " << it->first << " || second : " << it->second << '\n';
			}
			return out;
		}
		
		std::string get_target_file_fullpath(Request& req, Location& loc);
		std::string& get_file_resource(void);

		int get_pipe_write_fd(void);
		int get_pipe_read_fd(void);
		void set_pipe_write_fd(int fd);
		void set_pipe_read_fd(int fd);
		void load_file_resource(Request& req);
		std::string read_from_CGI_process(int timeout_ms);
		int write_to_CGI_process();
};

#endif