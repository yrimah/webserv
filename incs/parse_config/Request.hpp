#pragma once

#include <map>
#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <vector>
#include "StatusCodes.hpp"

class Request
{
    public :
        std::string method;
        std::string path;
        std::string http_version;
        std::string value;
        std::string key;
        std::string Port;
        std::string Host;
        std::string Index_file;
        bool Head_send;
        bool indexFile_open;
        bool send_filed;
        int indexFile_fd;
        std::string Size_ofFile;
        std::map<std::string, std::string> request_head;
        std::vector<std::string> listingFolder_files;
        char BufReadIndex[1024];
        ssize_t readByte;
        ssize_t sendByte;

        //
        std::string query_string;
    public :
        Request();
        ~Request();
        void read_request(char b[]);
        uint16_t Get_port();
        in_addr_t Get_host();

};


