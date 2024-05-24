#include "Error_page.hpp"

void Error_page::sendpage(int client_sock, std::string fileContent, std::string response)
{
	std::ostringstream oss;
	oss << response;	
 	oss << "Content-Length: " << fileContent.size() << "\r\n";
	oss << "\r\n";
	oss << fileContent;
	std::string header = oss.str();
	int bytes_sent = write(client_sock, header.c_str(), header.size()+1);
	if (bytes_sent == -1) {
            perror("send failed");
            return;
        }

}

std::string join(std::vector<std::string> lines, std::string delims)
{
	std::string joined = "";
	
	for(unsigned int i = 0; i < lines.size(); i++)
	{
		joined += lines.at(i);
		if ( i < lines.size()-1)
			joined += delims;
	}
	
	return joined;
}

void Error_page::send_error_page(Server server, std::string uri, int client_fd, int error_code, std::string text, Location location)
{
	std::string server_name = "Server: "+server.get_server_name();
	std::string response = "";
	std::stringstream ss;
	
	ss << error_code;
	std::string error_code_str = "HTTP/1.1 "+ss.str()+ " "+text;
	response += (error_code_str);
	response += (server_name);
	response += ("Content-Type: text/html");
	response += ("\r\n");

	//if(location.get_path() == uri)
	//{
		(void)uri;
		std::string error_page;
		if ((error_page = search_error_page(location.get_error_page(), error_code)) != "")
		{
			std::string error_path = server.get_root() + error_page;
			std::ifstream in_file(error_path.c_str());
			
			if (in_file.is_open()) 
			{
				std::string buffer = std::string((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
				Error_page::sendpage(client_fd, buffer, response);
				in_file.close();
				return;
			}
		}
	//}
	

	//std::string error_page;
	if ((error_page = search_error_page(server.get_error_page(), error_code)) != "")
	{
		std::string error_path = server.get_root() + error_page;
		std::ifstream in_file(error_path.c_str());
	
		if (in_file.is_open()) 
		{
			std::string buffer = std::string((std::istreambuf_iterator<char>(in_file)), std::istreambuf_iterator<char>());
			Error_page::sendpage(client_fd, buffer, response);
			in_file.close();
			return;
		}
	}
	std::string default_error = "<html><body><center><h2>HTTP/1.1 "+ss.str()+" "+text+"</h2></center></body></html>";
	Error_page::sendpage(client_fd, default_error, response);
	return;
}

std::string Error_page::search_error_page(std::vector<error_pages> error_page, int error_code)
{
	for (unsigned int i = 0; i < error_page.size(); i++)
	{
		if (error_page.at(i).code == error_code)
		{
			return error_page.at(i).path;
		}
	}
	return "";
}