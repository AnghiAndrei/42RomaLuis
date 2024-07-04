#include"webserv.hpp"

server::server(webserv &master){
    std::ostringstream cy;
    cy << master.get_n_server() + 1;
    std::string n_server = cy.str();
	error404="./dsite/404.html";
	error418="./dsite/418.html";
	root_assets="./dsite";
    name_server="Server"+n_server;
	index="index.html";
    root="./dsite";
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

std::string parseRequest(const std::string &request) {
    std::istringstream requestStream(request);
    std::string method, url, protocol;
    requestStream >> method >> url >> protocol;
    if (method != "GET") {
        return "";
    }
    return url;
}

std::string get_metod(const std::string &request) {
    std::istringstream requestStream(request);
    std::string method, url, protocol;
    requestStream >> method >> url >> protocol;
    return method;
}

bool endsWith(const std::string &str, const std::string &suffix){return str.size() >= suffix.size() && str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;}
std::string getext(const std::string &path){
    if (endsWith(path, ".html"))
        return "text/html";
	else if (endsWith(path, ".php"))
        return "text/html";
    else if (endsWith(path, ".sh"))
        return "text/html";
    else if (endsWith(path, ".python"))
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