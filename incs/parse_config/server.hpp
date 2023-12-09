#pragma once

#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include "conf_parser.hpp"
#include <cstring>
#include <fcntl.h>
#include <algorithm>
#include "Request.hpp"
#include "StatusCodes.hpp"
#include <sys/types.h>
#include <dirent.h>

#define MAX_EVN 1024

class server
{
public:
    std::vector<int> soket_fd;
    std::vector<int> client_fd;
    int epoll_fd;
    std::vector<int> p;
    std::map<int, Request> hand;
    bool flag;
    char buff[1024];
    Conf_parser serv;
    StatusCodes s;
    std::map<std::string, std::string> Extentions;
    //for post
    int rest;
    int length;
    int numR;
    int i;
    bool f;
    int readsize;
    int readflag;
    ssize_t _read;
    std::string header;
    std::string body;
    std::ofstream k;

    //
    // std::string query_string;

public:
    server();
    void creat_servers();
    void RecDelete(const char *path, int fd);
    void bindAnd_ListenServers();
    void Request_handling(int fd);
    bool Read_Request(int fd);
    void Get_handling(int fd);
    void Delete_handling(int fd);
    std::string GetLocationPath(int fd);
    bool CheckLocIndex_file(int fd);
    bool CheckServIndex_file(int fd);
    bool Check_Cgi(int fd);
    bool CheckLocAuto_index(int fd);
    bool CheckServAuto_index(int fd);
    void OpenLocIDXFile_forSend(const char *path, int fd);
    void OpenServIDXFile_forSend(int fd);
    void sendServIndex_file(int fd, DIR *dir);
    void OpenFile_forSend(const char *path, int fd);
    void send_locAutoIndex(const char *path, int fd, DIR *dir);
    void store_filesOf_listingFolder(DIR *dir, int fd);
    void ReadAnd_SendContent(int fd, DIR *dir);
    std::string Get_file_Extention(const char *path);
    void Store_extention();
    void sendHandel(int fd, int read, int send, DIR *dir);
    void GetCgiFalse(const char *path, int fd, DIR *dir);
    std::string get_path(int fd);
    void Get_F(const char *path, int fd);
    std::ofstream & creat_file(int fd);
    /// 
    /// for post
    void PostBoudary(int fd);
    void Post(int fd);
    void rest_bady(int fd, std::ofstream &file);

    ~server();
    class Filed_creatSocket : public std::exception
    {
    public:
        const char *what() const throw();
    };
    class Filed_epoll : public std::exception
    {
    public:
        const char *what() const throw();
    };
    class Filed_bind : public std::exception
    {
    public:
        const char *what() const throw();
    };
    class Filed_listen : public std::exception
    {
    public:
        const char *what() const throw();
    };
};
