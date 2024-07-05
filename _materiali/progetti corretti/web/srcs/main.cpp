#include "../includes/ServerManager.hpp"
#include "../includes/ConfigParser.hpp"

int main(int argc, char **argv)
{
	if (argc > 2)
		return 0;

	std::cout << GRN "=================================================\n";
	std::cout << "                 Webserv Start!                  \n";
	std::cout << "=================================================\n" WHT;

	std::string config = (argc == 1) ? "./config/default.config" : argv[1];
	ConfigParser configParser(config.c_str());
	std::vector<Server> *servers = configParser.parse();
	ServerManager manager(*servers);
	manager.print_servers_info();

	manager.create_servers();
	while (1)
	{
		manager.wait_to_client();
		manager.accept_sockets();
		manager.treat_request();
	}
	std::cout << "> Closing socket...\n";
	manager.close_servers();
	
	std::cout << GRN "=================================================\n";
	std::cout << "                Webserv Finished                 \n";
	std::cout << "=================================================\n" WHT;
	delete servers;
	return 0;
}