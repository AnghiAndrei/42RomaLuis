#ifndef WEBSERV_HPP
#define WEBSERV_HPP
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<sys/time.h>
#include<sys/stat.h>
#include<algorithm>
#include<unistd.h>
#include<signal.h>
#include<dirent.h>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<fcntl.h>
#include<string>
#include<vector>
#include<poll.h>
#include<map>

#define EXECUTION_TIME_LIMIT 10
#define BUFFER_SIZE1 1
#define BUFFER_SIZE 16384

class server;
class webserv;
class location;
struct t_master;

t_master leggi_file(std::string &locate, std::string &filePath, int fdc, server &server, char **env, std::string &query_get, std::string &query_post);
t_master execute(std::string &locate, int fdc, server &server, const std::string &request, char **env, std::string &get_query, std::string &post_query);
bool endsWith(const std::string &str, const std::string &suffix);
std::string ExtractFile(const std::string &directoryPath);
std::string ExtractPath(const std::string &directoryPath);
unsigned long long int stoull(const std::string &str);
int check(int argc, char **argv, webserv *webservv);
std::string readFile(const std::string &filePath);
std::string getext(const std::string &path);
std::string ExtensionFile(std::string nome);
bool dirExists(const std::string &path);
bool fileExists(const char *path);
void printWebserv(webserv &ws);
int setnblocking(int socket);

struct t_master{
	std::string content;
	int status;
};

class location{
	private:
		std::vector<std::string> med_allow;
		std::vector<std::string> ridirect;
		std::string body_size;
		std::string showdir;
		std::string index;
		std::string root;

	public:
		std::map<std::string, std::string> gci;

		~location(){}
		location(){
			root="";
			index="";
			showdir="yes";
			body_size="-1";
		}

		void set_body_size(std::string copy){body_size=copy;}
		void set_showdir(std::string copy){showdir=copy;}
		void set_index(std::string copy){index=copy;}
		void set_root(std::string copy){root=copy;}
		std::string get_root(){return root;}
		std::string get_index(){return index;}
		std::string get_showdir(){return showdir;}
		std::string get_body_size(){return body_size;}

		void set_medallow(std::vector<std::string> copy){this->med_allow.insert(med_allow.begin(), copy.begin(), copy.end());}
		std::string get_medallow(size_t index){return med_allow[index];}
		size_t get_lmedallow(){return med_allow.size();}
		bool is_allow_metod(std::string metod){
			std::vector<std::string>::iterator temp=std::find(med_allow.begin(), med_allow.end(), metod);
			if(temp!=med_allow.end())
				return true;
			return false;
		}

		void set_ridirect(std::vector<std::string> copy){this->ridirect.insert(ridirect.begin(), copy.begin(), copy.end());}
		std::string get_ridirect(size_t index){return ridirect[index];}
		size_t get_lridirect(){return ridirect.size();}
};

class server{
	private:
		std::string name_server;
		std::string error404;
		std::string error405;
		std::string error418;
		std::string error413;
		std::string error500;
		int socketserverfd;
		std::string host;
		int port;

	public:
		std::map<std::string, location> locations;

		~server(){/*close(socketserverfd);*/}
		server(webserv &master);

		std::map<std::string, std::string> gci;


		void set_error404(std::string &copy){error404=copy;}
		void set_error405(std::string &copy){error405=copy;}
		void set_error418(std::string &copy){error418=copy;}
		void set_error413(std::string &copy){error413=copy;}
		void set_error500(std::string &copy){error500=copy;}
		void set_name(std::string &copy){name_server=copy;}
		void set_host(std::string &copy){host=copy;}
		void set_port(int copy){port=copy;}
		int get_port(){return port;}
		std::string get_host(){return host;}
		int get_fd(){return socketserverfd;}
		std::string get_name(){return name_server;}
		std::string get_error500(){return error500;}
		std::string get_error418(){return error418;}
		std::string get_error413(){return error413;}
		std::string get_error404(){return error404;}
		std::string get_error405(){return error405;}

		void start(){
			struct sockaddr_in address;
			int opt = 1;

			if((socketserverfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
				std::cout<<"Marshal: Socket failed"<<std::endl;
				exit(-1);
			}
			if(setsockopt(socketserverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
				std::cout<<"Marshal: Setsockopt failed"<<std::endl;
				exit(-1);
			}
			address.sin_family = AF_INET;
			address.sin_addr.s_addr = INADDR_ANY;
			address.sin_port = htons(port);
			if(bind(socketserverfd, (struct sockaddr *)&address, sizeof(address))<0){
				std::cout<<"Marshal: Bind failed"<<std::endl;
				exit(-1);
			}
			if(listen(socketserverfd, 3)<0){
				std::cout<<"Marshal: Listen failed"<<std::endl;
				exit(-1);
			}
			setnblocking(socketserverfd);
		}
};

class webserv{
	size_t nserv;
	public:
		std::vector<server> servers;

		void crea_server(){servers.push_back(server(*this));}
		size_t	get_n_server(){return servers.size();}
		void set_nserv(size_t serv){this->nserv=serv;}
		webserv(){nserv=0;}
		~webserv(){}
};
#endif