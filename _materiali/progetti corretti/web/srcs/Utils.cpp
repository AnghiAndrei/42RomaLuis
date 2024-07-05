#include "../includes/Utils.hpp"

int replace(std::string &original, std::string word1, std::string word2)
{
	unsigned long pos = original.find(word1);
	int result = 0;
	while (pos != std::string::npos)
	{
		result = 1;
		original = original.replace(pos, word1.length(), word2);
		pos = original.find(word1);
	}
	return result;
}

std::string dir_listing()
{
	std::string path = "www/html/data/";
	DIR *dir;
	struct dirent *ent;
	dir = opendir(path.c_str());

	std::string result = "<ul>";
	while ((ent = readdir(dir)) != NULL)
	{
		result += "<li><a href=\"" + (std::string)ent->d_name + ">" 
			+ (std::string)ent->d_name + "<\\a><\\li>";
	}
	result += "</ul>";
	return result;
}

std::vector<std::string> split(std::string input, char delimiter)
{
    std::vector<std::string> answer;
    std::stringstream ss(input);
    std::string temp;
 
    while (getline(ss, temp, delimiter))
        answer.push_back(temp);
 
    return answer;
}

std::string get_ip(int client_fd)
{
	struct sockaddr_in	client_addr;
	socklen_t			addr_len = sizeof(struct sockaddr_in);
	char				ip[16];

	getsockname(client_fd, (struct sockaddr *)&client_addr, &addr_len);
	strncpy(ip, inet_ntoa(client_addr.sin_addr), 16);
	return (ip);
}


// Mon, 16 May 2022 05:47:10 GMT
std::string get_current_date_GMT(void)
{
	time_t rawtime;
	struct tm *pm;
	char format[29];
	std::string ret;

	time(&rawtime);
	pm = gmtime(&rawtime);
	strftime(format, 29, "%a, %d %b %G %X GMT", pm);
	ret = format;
	return ret;
}

size_t StringToHexNumber(std::string input)
{
	std::stringstream convert;
	size_t ret = 0;
	convert << std::hex << input;
	convert >> ret;
	return ret;
}
