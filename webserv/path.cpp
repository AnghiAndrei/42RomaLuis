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

std::string getAbsolutePath2(const std::string &filename, const std::string &directory, int i) {
    DIR *dir = opendir(directory.c_str());
    if (dir == NULL) {
        return "";
    }

    struct dirent *entry;
	std::string fullPath="";
    while ((entry = readdir(dir)) != NULL) {
        std::string entryName = entry->d_name;
        if (entryName == "." || entryName == "..") {
            continue;
        }
        fullPath = directory + "/" + entryName;
        if (entry->d_type == DT_DIR) {
            std::string result = getAbsolutePath2(filename, fullPath, i);
            if (!result.empty()) {
                closedir(dir);
                return result;
            }
        } else if (entry->d_type == DT_REG) {
            if (entryName == filename) {
                closedir(dir);
				if(i==0)
    	            return directory;
    	        else
				    return fullPath;
            }
        }
    }
    closedir(dir);
    return directory;
}

std::string getAbsolutePathPath(const std::string &filename, int i) {
    char *pwd = getcwd(NULL, 0);
    if (pwd == NULL) {
        std::cout<<"Marshal: Errore in getcwd"<<std::endl;
        exit(-1);
    }
    std::string currentDirectory = pwd;
    free(pwd);
    return getAbsolutePath2(filename, currentDirectory, i);
}

std::string ExtractFile(const std::string &directoryPath){
	size_t pos = directoryPath.find_last_of("/\\");
    if (pos == std::string::npos) {
        return "";
    }
    return directoryPath.substr(pos + 1);
}

std::string GetRootPath(){
	char *pwd = getcwd(NULL, 0);
    if (pwd == NULL) {
        std::cout<<"Marshal: Errore in getcwd"<<std::endl;
        exit(-1);
    }
    std::string currentDirectory = pwd;
    free(pwd);
	return currentDirectory;
}


std::string getAbsolutePath4(const std::string &filename, const std::string &directory, int i) {
    DIR *dir = opendir(directory.c_str());
    if (dir == NULL) {
        return "";
    }

    struct dirent *entry;
	std::string fullPath="";
    while ((entry = readdir(dir)) != NULL) {
        std::string entryName = entry->d_name;
        if (entryName == "." || entryName == "..") {
            continue;
        }
        fullPath = directory + "/" + entryName;
		if(entry->d_type == DT_REG){
            if (entryName == filename) {
                closedir(dir);
				if(i==0)
    	            return directory;
    	        else
				    return fullPath;
            }
		}else{
            std::string result = getAbsolutePath4(filename, fullPath, i);
            if (!result.empty()) {
                closedir(dir);
                return result;
            }
		}
    }
    closedir(dir);
    return "";
}

std::string getAbsolutePath3(const std::string &filename, int i) {
    char *pwd = getcwd(NULL, 0);
    if (pwd == NULL) {
        std::cout<<"Marshal: Errore in getcwd"<<std::endl;
        exit(-1);
    }
    std::string currentDirectory = pwd;
    free(pwd);
    return getAbsolutePath4(filename, currentDirectory, i);
}