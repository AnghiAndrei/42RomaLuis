#include "Webserver.hpp"
#include "./parser_conf/Parser.hpp"

int check_serv(Server server);

int main(int argc, char *argv[], char *envp[]) {
	
	std::string config_file = "webserver.conf";
	std::vector<Server> servers;

	(void)envp;

	if (argc > 2) {
		std::cerr << "Usage: " << argv[0] << "<config_file>" << std::endl;
		return -1;
	}
	
	if (argc == 2)
		servers = Parser::config(argv[1]);
	else
		servers = Parser::config(config_file.c_str());

	//controllo se ci sono errori nella configurazione
	if (servers.size() == 0) {
		std::cerr << "Error: no server found in the configuration file" << std::endl;
		return -1;
	}

	//controllo se ci sono errori nella configurazione
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it) {
		if (check_serv(*it))
			return -1;
	}

	//ciclo tutti i server e se trovo delle porte uguali esco
	for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); ++it) {
		for (std::vector<Server>::iterator it2 = it + 1; it2 != servers.end(); ++it2) {
			if (it->get_listen() == it2->get_listen()) {
				std::cerr << "Error: two servers cannot listen on the same port" << std::endl;
				return -1;
			}
		}
	}
	
	Webserver webserver = Webserver();
	webserver.run(servers);
	
	return 0;

}

int check_serv(Server server) {
	if (server.get_server_name() == "") {
		std::cerr << "Error: server_name not found" << std::endl;
		return -1;
	}
	if (server.get_listen() < 1 ||  65535 < server.get_listen()) {
		std::cerr << "Error: invalid port" << std::endl;
		return -1;
	}
	if (server.get_root() == "") {
		std::cerr << "Error: root not found" << std::endl;
		return -1;
	}
	if (server.get_client_max_body_size() < 0) {
		std::cerr << "Error: invalid client_max_body_size" << std::endl;
		return -1;
	}
	//controllo se root esiste
	struct stat buffer;
	if (stat(server.get_root().c_str(), &buffer) != 0) {
		std::cerr << "Error: root does not exist" << std::endl;
		return -1;
	}
	return 0;
}