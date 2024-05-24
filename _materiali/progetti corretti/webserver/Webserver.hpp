#pragma once

#include <poll.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cerrno>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <map>
#include <sys/stat.h>

#include "./server/Server.hpp"
#include "./error/Error_page.hpp"
#include "./utilities/Utilities.hpp"
#include "./request/Request_manager.hpp"
#include "./get/Get_request.hpp"
#include "./post/Post_request.hpp"
#include "./delete/Delete_request.hpp"
#include "./server/Location.hpp"
class Webserver
{
public:
    Webserver(){};
    ~Webserver(){};

    int run(std::vector<Server> servers);
};