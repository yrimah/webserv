#include "../incs/parse_config/server.hpp"
#include <csignal>

server::server()
{
    _read = 0;
    readsize = 1024;
    readflag = true;
    numR = 0;
    length = 0;
    f = true;
    i = 0;
    // query_string = "";
}

void server::creat_servers()
{
    int soket_fd;
    for (int i = 0; i < serv.getServers_nbr(); i++)
    {
        if ((soket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            throw Filed_creatSocket();
        }
        p.push_back(soket_fd);
    }
}

void server::bindAnd_ListenServers()
{
    signal(SIGPIPE, SIG_IGN);
    int opt = -1;
    flag = false;
    int num_evn, client_socket;
    struct epoll_event evns[MAX_EVN];

    if ((epoll_fd = epoll_create1(0)) < 0)
        throw Filed_epoll();
    std::vector<Server_storage>::iterator it = serv.getServers().begin();
    for (std::vector<int>::iterator e = p.begin(); e < p.end(); it++, e++)
    {
        setsockopt(*e, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
        it->set_sockadde(it->getPort());
        struct sockaddr_in ServAdd = it->get_sockaddr();
        if (bind(*e, (const sockaddr *)&ServAdd, sizeof(ServAdd)) < 0)
            throw Filed_bind();
        if (listen(*e, 3) == -1)
            throw Filed_listen();
        struct epoll_event evn;
        evn.events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLRDHUP | EPOLLHUP;
        evn.data.fd = *e;
        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, *e, &evn) == -1)
            throw Filed_epoll();
    }
    while (1)
    {

        if ((num_evn = epoll_wait(epoll_fd, evns, MAX_EVN, -1)) < 0)
            throw Filed_epoll();
        for (int i = 0; i < num_evn; i++)
        {
            if (evns[i].data.fd <= p.back())
            {
                if ((client_socket = accept(evns[i].data.fd, NULL, NULL)) < 0)
                    throw std::runtime_error("Error : accept conection");
                else
                {
                    client_fd.push_back(client_socket);
                    struct epoll_event client_evn;
                    client_evn.events = EPOLLIN | EPOLLOUT;
                    client_evn.data.fd = client_socket;
                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &client_evn) < 0)
                    {
                        close(client_socket);
                        throw Filed_epoll();
                    }
                }
            }
            else
            {
                std::vector<int>::iterator etr = client_fd.begin();
                for (; etr != client_fd.end(); etr++)
                {
                    if (*etr == evns[i].data.fd)
                        break;
                }
                if (evns[i].events & EPOLLIN && readflag && !Read_Request(*etr))
                {
                    // std::cout << "====================reading======================" << std::endl;
                }
                else if (evns[i].events & EPOLLOUT && flag)
                {
                    // for (std::map<std::string, std::string>::iterator it = hand[*etr].request_head.begin(); it != hand[*etr].request_head.end(); it++)
                    // {
                    //     std::cout << it->first << ": " << it->second << std::endl;
                    // }
                    // std::cout << "  //////////////////-----  " << *etr << std::endl;
                    Request_handling(*etr);
                    // std::cout << "=====================sending=========================" << std::endl;
                    // std::cout << hand[*etr].path << std::endl;
                    //  send(*etr, "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 4\n\n hi!", 65, 0);
                    //  epoll_ctl(epoll_fd, EPOLL_CTL_DEL, *etr, 0);
                    //  hand.erase(*etr);
                    //  close(*etr);
                    //  flag = false;
                }
            }
        }
    }
}

void server::Request_handling(int fd)
{
    if (hand[fd].path != "/favicon.ico")
    {
        if (hand[fd].method == "GET")
        {
            Get_handling(fd);
        }
        else if (hand[fd].method == "POST")
        {
            Post(fd);
        }
        else if (hand[fd].method == "DELETE")
        {
            Delete_handling(fd);
        }
    }
    else
    {
       
        const char *response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Type: text/plain\r\n"
            "\r\n"
            "404 Not Found: The requested resource does not exist.";
        int sed = send(fd, response, strlen(response), 0);
        //std::cout <<sed<<std::endl;
            // epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);
            // close(hand[fd].indexFile_fd);
            // close(fd);
            // hand.erase(fd);
            readflag = false;
            flag = true;
    }
}

std::string server::get_path(int fd)
{
    // hand[fd].Get_host();
    std::vector<Server_storage>::iterator it = serv.getServers().begin();
    for (; it != serv.getServers().end(); it++)
    {
        if (it->getPort() == hand[fd].Get_port() && it->getHost() == hand[fd].Get_host())
        {
            for (std::vector<Location_storage>::iterator itr = it->_locations.begin(); itr != it->_locations.end(); itr++)
            {
                if (GetLocationPath(fd) == itr->getLocaPath())
                {
                    if (itr->getLocaAllowedMethods().at(2) == 0)
                        throw std::runtime_error("not alowed method");
                    std::string p = itr->getLocaRoot();
                    if (!p.empty())
                    {
                        p += &hand[fd].path[1];
                    }
                    else
                    {
                        p = it->getRoot();
                        p += &hand[fd].path[1];
                    }
                    size_t query = p.find("?");
                    if (query == std::string::npos)
                        return (p);
                    else
                    {
                        hand[fd].query_string = p.substr(query + 1);
                        p.erase(query);
                        return (p);
                    }
                }
            }
        }
    }
    return (NULL);
}

std::string server::GetLocationPath(int fd)
{
    std::string pathHold = &hand[fd].path[1];
    size_t pos = pathHold.find('/');
    if (pos == std::string::npos && hand[fd].path.length() == 1)
        return (hand[fd].path);
    std::string pathReturn = hand[fd].path.substr(0, pos + 1);
    return pathReturn;
}

bool checkDirIsEmpty(const char *path)
{
    DIR *dir = opendir(path);
    if (dir)
    {
        struct dirent *centent;
        while ((centent = readdir(dir)) != NULL)
        {
            if (strcmp(centent->d_name, ".") != 0 && strcmp(centent->d_name, "..") != 0)
            {
                closedir(dir);
                return false;
            }
        }
        closedir(dir);
        return true;
    }
    return false;
}

void server::RecDelete(const char *path, int fd)
{
    DIR *dir = opendir(path);
    if (dir)
    {
        ;
        struct dirent *centent;
        while ((centent = readdir(dir)) != NULL)
        {
            if (strcmp(centent->d_name, ".") != 0 && strcmp(centent->d_name, "..") != 0)
            {
                std::string re(path);
                re += "/";
                re += centent->d_name;
                RecDelete(re.c_str(), fd);
            }
        }
        if (checkDirIsEmpty(path))
        {
            std::string rem = "rm -rf ";
            rem += path;
            std::system(rem.c_str());
        }
    }
    else
    {
        if (access(path, X_OK) == 0)
        {
            if (std::remove(path) != 0)
                throw std::runtime_error("cant remove file");
            send(fd, s.NoContent_204.c_str(), s.NoContent_204.length(), 0);
        }
        else
        {
            s.Forbidden_403 += "Content-Type: text/plain\r\n"
                               "\r\n"
                               "403 FORBIDDEN";
            send(fd, s.Forbidden_403.c_str(), s.Forbidden_403.length(), 0);
        }
    }
}

void server::Delete_handling(int fd)
{
    try
    {
        if (access(get_path(fd).c_str(), F_OK) != 0)
        {
            const char *response =
                "HTTP/1.1 404 Not Found\r\n"
                "Content-Type: text/plain\r\n"
                "\r\n"
                "404 Not Found: The requested resource does not exist.";
            send(fd, response, strlen(response), 0);
        }
        else
            RecDelete(get_path(fd).c_str(), fd);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        send(fd, s.Method_NAllowed_405.c_str(), s.Method_NAllowed_405.length(), 0);
    }
}

bool server::Read_Request(int fd)
{
    memset(buff, 0, 1024);
    int f = recv(fd, buff, 1024, 0);
    header.append(buff, f);
    size_t pos = header.find("\r\n\r\n");
    if (pos != std::string::npos)
    {
        readflag = false;
        std::string re = header.substr(0, pos + 2);
        std::cout<<re<<std::endl;
        rest = f - pos - 4;
        body = header.substr(pos + 4, rest);
        char ar[re.length() + 1];
        std::strcpy(ar, re.c_str());
        hand[fd].read_request(ar);
        header.clear();
        flag = true;
        return true;
    }
    return (false);
}

/// ////////////////
/// exceptions /
const char *server::Filed_creatSocket::what() const throw()
{
    return ("Error");
}

const char *server::Filed_bind::what() const throw()
{
    return ("Error : bind function");
}

const char *server::Filed_listen::what() const throw()
{
    return ("Error : listen function");
}

const char *server::Filed_epoll::what() const throw()
{
    return ("Error : epoll functions");
}

server::~server()
{
}