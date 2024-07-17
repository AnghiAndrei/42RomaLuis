#include"webserv.hpp"

server::server(webserv &master){
    std::ostringstream cy;
    cy << master.get_n_server() + 1;
    std::string n_server = cy.str();
	error404="/nfs/homes/aanghi/Desktop/42RomaLuis/webserv/dsite/404.html";
	error405="/nfs/homes/aanghi/Desktop/42RomaLuis/webserv/dsite/405.html";
	error418="/nfs/homes/aanghi/Desktop/42RomaLuis/webserv/dsite/418.html";
	error413="/nfs/homes/aanghi/Desktop/42RomaLuis/webserv/dsite/413.html";
	error500="/nfs/homes/aanghi/Desktop/42RomaLuis/webserv/dsite/500.html";
	root_assets="/nfs/homes/aanghi/Desktop/42RomaLuis/webserv/dsite/";
    name_server="Server"+n_server;
	index="index.html";
    root="/nfs/homes/aanghi/Desktop/42RomaLuis/webserv/dsite/";
    showdir="yes";
    body_size="";
    host="";
    port=-1;
}

int setnblocking(int socket) {
    int flags=fcntl(socket, F_GETFL, 0);
    if(flags==-1){
		std::cout<<"Marshal: Fcntl failed"<<std::endl;
        exit(-1);
    }
    flags |= O_NONBLOCK;
    if (fcntl(socket, F_SETFL, flags) == -1) {
        std::cout<<"Marshal: Fcntl failed"<<std::endl;
        exit(-1);
    }
    return 0;
}

std::string readFile(const std::string &filePath) {
    std::ifstream file(filePath.c_str());
    if (!file.is_open()) {
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

bool endsWith(const std::string &str, const std::string &suffix){return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;}
std::string getext(const std::string &path){
    if (endsWith(path, ".html"))
        return "text/html";
	else if (endsWith(path, ".php"))
        return "text/html";
    else if (endsWith(path, ".sh"))
        return "text/html";
    else if (endsWith(path, ".py"))
        return "text/html";
    else if (endsWith(path, ".css"))
        return "text/css";
    else if (endsWith(path, ".js"))
        return "application/javascript";
    else if (endsWith(path, ".png"))
        return "image/png";
	else if (endsWith(path, ".jpg") || endsWith(path, ".jpeg"))
        return "image/jpeg";
    else
        return "application/octet-stream";
}

t_master leggi_file(std::string &filePath, int fdc, server &server, char **env, std::string &query_get, std::string &query_post){
	if(server.gci.find(ExtensionFile(filePath)) == server.gci.end()){
	    t_master ris;
		ris.content=readFile(filePath);
		ris.status=0;
        return ris;
    }
    return execute(fdc, server, filePath, env, query_get, query_post);
}

unsigned long long int stoull(const std::string &str) {
    unsigned long long int result = 0;
    std::istringstream iss(str);
    iss >> result;
    return result;
}