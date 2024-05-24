#include "AutoIndex.hpp"

std::string AutoIndex::createAutoIndex(Server servers, std::string path, std::string root) {

    std::stringstream ss;
    DIR *dir;
    struct dirent *entry;
    std::stringstream port;
    port << servers.get_listen();
    ss << HTML_TOP;

    if (path != "/")
        path += "/";

    if ((dir = opendir((root + path).c_str())) != NULL) {
        while ((entry = readdir(dir)) != NULL) {
            if ((entry->d_type == DT_DIR || entry->d_type == DT_REG) // gets only directories or files
                        && (entry->d_name[0] != '.' || !entry->d_name[1] // removes all hidden files and folders
                        || (entry->d_name[1] == '.' && !entry->d_name[2])))
                ss << "<a href=\"" << URL_TEMPLATE(servers.get_server_name() + ":" + port.str(), path + entry->d_name) << "\">" << entry->d_name << "</a><br>\n";
        }
        closedir(dir);
    } else
        std::cerr << "Impossibile aprire la cartella." << std::endl;
    ss << HTML_BOT;
    return ss.str();
}