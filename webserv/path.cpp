#include"webserv.hpp"

bool fileExists(const char *path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

bool dirExists(const std::string &path){
    struct stat info;
    if(stat(path.c_str(), &info)!=0)
		return false;
	return true;
}

std::string ExtractFile(const std::string &directoryPath){
	size_t pos = directoryPath.find_last_of("/\\");
    if (pos == std::string::npos)
        return "";
    return directoryPath.substr(pos + 1);
}

std::string ExtractPath(const std::string &directoryPath){
	size_t pos = directoryPath.find_last_of("/\\");
    if (pos == std::string::npos)
		return "";
    return directoryPath.substr(0, pos);
}

std::string ExtensionFile(std::string nome){
    size_t pos = nome.rfind('.');
    if (pos == std::string::npos || pos == 0)
        return "";
    return nome.substr(pos);
}