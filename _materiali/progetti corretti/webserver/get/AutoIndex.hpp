#pragma once

#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sys/socket.h>
#include <sstream>
#include <dirent.h>

#define HTML_TOP "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>AutoIndex</title></head><body><p>AutoIndex</p>"
#define HTML_BOT "</body></html>"
#define URL_TEMPLATE(host, path) std::string("http://") + host + path


#include "../server/Server.hpp"
#include "../server/Location.hpp"
#include "../utilities/Utilities.hpp"


class AutoIndex {
    public:
        static std::string  createAutoIndex(Server servers, std::string path, std::string root);
};