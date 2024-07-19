#include "../webserv.hpp"

void printLocation(location &loc) {
    std::cout << "        Body Size: " << loc.get_body_size() << std::endl;
    std::cout << "        Show Directory: " << loc.get_showdir() << std::endl;
    std::cout << "        Index: " << loc.get_index() << std::endl;
    std::cout << "        Root: " << loc.get_root() << std::endl;

    std::cout << "        Allowed Methods:" << std::endl;
    for (size_t i = 0; i < loc.get_lmedallow(); ++i) {
        std::cout << "          " << loc.get_medallow(i) << std::endl;
    }

    std::cout << "        Redirects:" << std::endl;
    for (size_t i = 0; i < loc.get_lridirect(); ++i) {
        std::cout << "          " << loc.get_ridirect(i) << std::endl;
    }

    std::cout << "        CGI:" << std::endl;
    for (std::map<std::string, std::string>::iterator it = loc.gci.begin(); it != loc.gci.end(); ++it) {
        std::cout << "          " << it->first << ": " << it->second << std::endl;
    }
}

void printServer(server &srv) {
    std::cout << "Server:" << std::endl;
    std::cout << "  Name: " << srv.get_name() << std::endl;
    std::cout << "  Host: " << srv.get_host() << std::endl;
    std::cout << "  Port: " << srv.get_port() << std::endl;
    std::cout << "  Error 404: " << srv.get_error404() << std::endl;
    std::cout << "  Error 405: " << srv.get_error405() << std::endl;
    std::cout << "  Error 418: " << srv.get_error418() << std::endl;
    std::cout << "  Error 413: " << srv.get_error413() << std::endl;
    std::cout << "  Error 500: " << srv.get_error500() << std::endl;

    std::cout << "  Locations:" << std::endl;
    for (std::map<std::string, location>::iterator it = srv.locations.begin(); it != srv.locations.end(); ++it) {
        std::cout <<"    Path: " << it->first << std::endl;
        printLocation(it->second);
    }
}

void printWebserv(webserv &ws) {
    std::cout << "Webserv:" << std::endl;
    std::cout << "  Number of Servers: " << ws.get_n_server() << std::endl;

    for (size_t i = 0; i < ws.get_n_server(); ++i) {
        std::cout << "  Server " << i + 1 << ":" << std::endl;
        printServer(ws.servers[i]);
    }
}