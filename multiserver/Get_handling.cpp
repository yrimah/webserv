#include "../incs/parse_config/server.hpp"
#include "../incs/cgi_config/cgi_conf.hpp"
#include <csignal>
#include <sys/types.h>
#include <sys/wait.h>


void server::Get_handling(int fd)
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
        Get_F(get_path(fd).c_str(), fd);
}

void server::OpenLocIDXFile_forSend(const char *path, int fd)
{
    std::string pathIndex(path);
    pathIndex += "/";
    pathIndex += hand[fd].Index_file;
    std::cout <<pathIndex<<std::endl;
    int fd_index;
    if (hand[fd].indexFile_open == false)
    {
        fd_index = open(pathIndex.c_str(), O_RDONLY);
        struct stat FileInfo;
        fstat(fd_index, &FileInfo);
        std::ostringstream s;
        s << FileInfo.st_size;
        hand[fd].Size_ofFile = s.str();
        hand[fd].indexFile_fd = fd_index;
        hand[fd].indexFile_open = true;
    }
}

void server::OpenServIDXFile_forSend(int fd)
{
    std::string pathIndex;
    int fd_index;
    if (hand[fd].indexFile_open == false)
    {
        std::vector<Server_storage>::iterator it = serv.getServers().begin();
        for (; it != serv.getServers().end(); it++)
        {
            if (it->getPort() == hand[fd].Get_port() && it->getHost() == hand[fd].Get_host())
            {
                pathIndex = it->getIndex();
                std::cout << "===================== " << pathIndex << std::endl;
            }
        }
        fd_index = open(pathIndex.c_str(), O_RDONLY);
        struct stat FileInfo;
        fstat(fd_index, &FileInfo);
        std::ostringstream s;
        s << FileInfo.st_size;
        hand[fd].Size_ofFile = s.str();
        hand[fd].indexFile_fd = fd_index;
        hand[fd].indexFile_open = true;
    }
}

void server::OpenFile_forSend(const char *path, int fd)
{
    int fd_index;
    if (hand[fd].indexFile_open == false)
    {
        fd_index = open(path, O_RDONLY);
        struct stat FileInfo;
        fstat(fd_index, &FileInfo);
        std::ostringstream s;
        s << FileInfo.st_size;
        hand[fd].Size_ofFile = s.str();
        hand[fd].indexFile_fd = fd_index;
        hand[fd].indexFile_open = true;
    }
}

void server::GetCgiFalse(const char *path, int fd, DIR *dir)
{
    OpenLocIDXFile_forSend(path, fd);
    if (!hand[fd].Head_send)
    {
        s.OK_200 += "Content-Type: video/mp4\r\nContent-Length: ";
        s.OK_200 += hand[fd].Size_ofFile;
        s.OK_200 += "\r\n\r\n";
        ssize_t sendH = send(fd, s.OK_200.c_str(), s.OK_200.length(), 0);
        sendHandel(fd, s.OK_200.length(), sendH, dir);
        s.OK_200.clear();
        s.OK_200 = "HTTP/1.1 200 ok\r\n";
        hand[fd].Head_send = true;
    }
    else
    {
        ReadAnd_SendContent(fd, dir);
    }
}

void server::sendServIndex_file(int fd, DIR *dir)
{
    OpenServIDXFile_forSend(fd);
    if (!hand[fd].Head_send)
    {
        s.OK_200 += "Content-Type: image/jpeg\r\nContent-Length: ";
        s.OK_200 += hand[fd].Size_ofFile;
        s.OK_200 += "\r\n\r\n";
        ssize_t sendH = send(fd, s.OK_200.c_str(), s.OK_200.length(), 0);
        sendHandel(fd, s.OK_200.length(), sendH, dir);
        s.OK_200.clear();
        s.OK_200 = "HTTP/1.1 200 ok\r\n";
        hand[fd].Head_send = true;
    }
    else
    {

        ReadAnd_SendContent(fd, dir);
    }
}

void server::sendHandel(int fd, int read, int send, DIR *dir)
{
    if (send < 1)
    {
        hand[fd].send_filed = true;
    }
    else if (send == read)
    {
        hand[fd].send_filed = true;
    }
    else if (send < read)
    {
        read -= send;
        hand[fd].send_filed = false;
    }
}

void server::ReadAnd_SendContent(int fd, DIR *dir)
{
    ////
    ////
    ////
    if (hand[fd].send_filed)
    {
        hand[fd].readByte = read(hand[fd].indexFile_fd, hand[fd].BufReadIndex, sizeof(hand[fd].BufReadIndex));
        std::cout << hand[fd].BufReadIndex << std::endl;
        if (hand[fd].readByte < 1)
        {
            std::cout << "STTDDD\n";
            std::cout<<hand[fd].readByte<<std::endl;
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);
            close(hand[fd].indexFile_fd);
            close(fd);
            hand.erase(fd);
            readflag = true;
            flag = false;
            if (dir)
                closedir(dir);
        }
        if (hand[fd].readByte < 1024)
        {
            // std::cout << hand[fd].readByte << "STTqqqqqqqq\n";
            // std::string len = hand[fd].readByte; 
            std::string subBufF(hand[fd].BufReadIndex, hand[fd].BufReadIndex + hand[fd].readByte);
            // std::string r = "HTTP/1.1 200 OK\r\n";
            // r += "Content-Type: text/html\r\n";
            // r += "Content-Length: " + subBufF.length();
            //
            // size_t cookie_pos = subBufF.find("set-cookie");
            // std::cout << "BEFOOORE\n";
            // if (cookie_pos != std::string::npos)
            // {
            //     std::string cookie = subBufF.substr(cookie_pos, subBufF.find_last_of("\r\n"));
            //     r += "\r\n" + cookie;
            //     std::cout << cookie << "PPPPPOOOOOOOOF\n";
            // }
            //
            // r +=  "\r\n" + subBufF;
            // subBufF = r;
            // std::cout << subBufF << "::::::\n";
            subBufF += "\r\n\r\n";
            hand[fd].sendByte = send(fd, subBufF.c_str(), subBufF.length(), 0);
            sendHandel(fd, subBufF.length(), hand[fd].sendByte, dir);
            epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);
            close(hand[fd].indexFile_fd);
            close(fd);
            hand.erase(fd);
            readflag = true;
            flag = false;
            if (dir)
                closedir(dir);
        }
        hand[fd].sendByte = send(fd, hand[fd].BufReadIndex, hand[fd].readByte, 0);
        sendHandel(fd, hand[fd].readByte, hand[fd].sendByte, dir);
    }
    else
    {
        hand[fd].sendByte = send(fd, hand[fd].BufReadIndex, hand[fd].readByte, 0);
        sendHandel(fd, hand[fd].readByte, hand[fd].sendByte, dir);
    }
}

void server::store_filesOf_listingFolder(DIR *dir, int fd)
{
    struct dirent *centent;
    while ((centent = readdir(dir)) != NULL)
    {
        if (strcmp(centent->d_name, ".") != 0 && strcmp(centent->d_name, "..") != 0)
        {
            hand[fd].listingFolder_files.push_back(centent->d_name);
        }
    }
}

void server::send_locAutoIndex(const char *path, int fd, DIR *dir)
{
    (void)path;
    std::string htmlStr;
    htmlStr = "<!DOCTYPE html>\n<html>\n<head>\n<title>Folder Listing</title>\n</head>\n<body>"
              "\n<h1>Folder Listing</h1>"
              "\n<ul>\n";
    struct dirent *centent;
    while ((centent = readdir(dir)) != NULL)
    {
        if (strcmp(centent->d_name, ".") != 0 && strcmp(centent->d_name, "..") != 0)
        {
            htmlStr += "<li><a href=\"";
            htmlStr += centent->d_name;
            htmlStr += "\">";
            htmlStr += centent->d_name;
            htmlStr += "</a>";
        }
    }
    // store_filesOf_listingFolder(dir, fd);
    //  std::vector<std::string>::iterator itr = hand[fd].listingFolder_files.begin();
    //   for()
    if (!hand[fd].Head_send)
    {
        std::cout<<"here send auto index header\n";
        s.OK_200 += "Content-Type: image/html\r\nContent-Length: ";
        s.OK_200 += hand[fd].Size_ofFile;
        s.OK_200 += "\r\n\r\n";
        ssize_t sendH = send(fd, s.OK_200.c_str(), s.OK_200.length(), 0);
        sendHandel(fd, s.OK_200.length(), sendH, dir);
        s.OK_200.clear();
        s.OK_200 = "HTTP/1.1 200 ok\r\n";
        hand[fd].Head_send = true;
    }
    else
    {
        std::cout <<htmlStr<<std::endl;
        hand[fd].sendByte = send(fd, htmlStr.c_str(), htmlStr.length(), 0);
        sendHandel(fd, htmlStr.length(), hand[fd].sendByte, dir);
        epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);
        close(hand[fd].indexFile_fd);
        close(fd);
        hand.erase(fd);
        flag = false;
        if (dir)
            closedir(dir);
    }
}

void server::Get_F(const char *path, int fd)
{
    DIR *dir = opendir(path);
    if (dir)
    {
        if (!CheckLocAuto_index(fd))
        {
            if (CheckLocIndex_file(fd))
            {
                if (Check_Cgi(fd))
                {
                    // std::cout << "YEEEES CGII\n";
                }
                else if (!Check_Cgi(fd))
                {
                    GetCgiFalse(path, fd, dir);
                }
            }
            else if (CheckServIndex_file(fd))
            {
                sendServIndex_file(fd, dir);
            }
            else
            {
                s.Forbidden_403 += "Content-Type: text/plain\r\n"
                                   "\r\n"
                                   "403 FORBIDDEN";
                send(fd, s.Forbidden_403.c_str(), s.Forbidden_403.length(), 0);
            }
        }
        else if (CheckLocAuto_index(fd))
        {
            send_locAutoIndex(path, fd, dir);
        }
        else if (CheckServAuto_index(fd))
        {
        }
    }
    else
    {
        if (!Check_Cgi(fd))
        {
            if (!hand[fd].Head_send)
            {
                std::string ext;
                std::string File_extention = Get_file_Extention(path);
                OpenFile_forSend(path, fd);
                for (std::map<std::string, std::string>::iterator it = Extentions.begin(); it != Extentions.end(); it++)
                {
                    if (File_extention == it->first)
                    {
                        ext = it->second;
                        break;
                    }
                }
                s.OK_200 += "Content-Type: ";
                s.OK_200 += ext;
                s.OK_200 += "\r\nContent-Length: ";
                s.OK_200 += hand[fd].Size_ofFile;
                s.OK_200 += "\r\n\r\n";
                ssize_t sendH = send(fd, s.OK_200.c_str(), s.OK_200.length(), 0);
                sendHandel(fd, s.OK_200.length(), sendH, dir);
                s.OK_200.clear();
                s.OK_200 = "HTTP/1.1 200 ok\r\n";
                hand[fd].Head_send = true;
            }
            else
            {
                ReadAnd_SendContent(fd, dir);
            }
        }
        else
        {
            // std::cout << "RIGHT\n";
            //
            std::string tmp = path;
            Cgi_conf cgi;
            cgi.clear();
            std::string new_path = tmp.substr(tmp.find_first_of("/") + 1);
            cgi.setPath(new_path);

            std::vector<Server_storage>::iterator it = serv.getServers().begin();
            std::vector<Location_storage>::iterator save;
            for (; it != serv.getServers().end(); it++)
            {
                if (it->getPort() == hand[fd].Get_port() && it->getHost() == hand[fd].Get_host())
                {
                    for (std::vector<Location_storage>::iterator itr = it->_locations.begin(); itr != it->_locations.end(); itr++)
                    {
                        if (itr->getLocaPath() == "/cgi-bin")
                        {
                            // std::cout << "TESSSSSS\n";
                            save = itr;
                        }
                    }
                }
            }
            int error = 0;
            int _cgi_fd[2];
            // if (pipe(_cgi_fd) < 0)
            // {
            //     error = 500;
            //     exit (1);
            // }
            cgi.initialize_cgi_env(hand[fd], save);
            cgi.cgi_executer(error);
            waitpid(cgi.cgi_id, NULL, 0);
            //
            // write(cgi.pipe_in[1], req_body.c_str(), req_body.length());
            // std::cout << "OOOOOOOOOOOPPPPPPP\n";
            char    buffer[40000 * 2];
            int     bytes_read = 0;
            // bytes_read = read(cgi._out[0], buffer, 40000 * 2);
            hand[fd].send_filed = true;
            hand[fd].indexFile_fd = cgi._out[0];
            // read(hand[fd].indexFile_fd, hand[fd].BufReadIndex, sizeof(hand[fd].BufReadIndex));
            // std::cout << "bytes read : " << bytes_read << "\n";
            // const char *response =
            // "HTTP/1.1 404 Not Found\r\n"
            // "Content-Type: text/plain\r\n"
            // "\r\n"
            // "404 Not Found: The requested resource does not exist.";
            // std::cout << buffer << "::teeeeeeeeeeer\n";
            // send(fd, buffer, strlen(buffer), 0);
            // sleep(10000000);
            ReadAnd_SendContent(fd, dir);
            //
        }
    }
}

void server::Store_extention()
{
    Extentions[".txt"] = "text/plain";
    Extentions[".html"] = "text/html";
    Extentions[".css"] = "text/css";
    Extentions[".js"] = "application/javascript";
    Extentions[".json"] = "application/json";
    Extentions[".xml"] = "application/xml";
    Extentions[".jpg"] = "image/jpeg";
    Extentions[".png"] = "image/png";
    Extentions[".gif"] = "image/gif";
    Extentions[".mp3"] = "audio/mpeg";
    Extentions[".mp4"] = "video/mp4";
    Extentions[".pdf"] = "application/pdf";
    Extentions[".doc"] = "application/msword";
    Extentions[".zip"] = "application/zip";
}

std::string server::Get_file_Extention(const char *path)
{
    std::string tofindFI(path + 1);
    size_t pos = tofindFI.find(".");
    std::string FileIn = tofindFI.substr(pos, tofindFI.length() - pos);
    return FileIn;
}

bool server::Check_Cgi(int fd)
{
    std::vector<Server_storage>::iterator it = serv.getServers().begin();
    for (; it != serv.getServers().end(); it++)
    {
        if (it->getPort() == hand[fd].Get_port() && it->getHost() == hand[fd].Get_host())
        {
            for (std::vector<Location_storage>::iterator itr = it->_locations.begin(); itr != it->_locations.end(); itr++)
            {
                size_t pos = GetLocationPath(fd).find("cgi");
                if (pos != std::string::npos)
                    return true;
            }
        }
    }
    return false;
}

bool server::CheckLocAuto_index(int fd)
{
    std::vector<Server_storage>::iterator it = serv.getServers().begin();
    for (; it != serv.getServers().end(); it++)
    {
        if (it->getPort() == hand[fd].Get_port() && it->getHost() == hand[fd].Get_host())
        {
            for (std::vector<Location_storage>::iterator itr = it->_locations.begin(); itr != it->_locations.end(); itr++)
            {
                if (GetLocationPath(fd) == itr->getLocaPath())
                {
                    if (itr->getLocaAutoindex() == true)
                    {
                        std::cout<<"here in get location path\n"<<itr->getLocaAutoindex()<<std::endl;

                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool server::CheckServAuto_index(int fd)
{
    std::vector<Server_storage>::iterator it = serv.getServers().begin();
    for (; it != serv.getServers().end(); it++)
    {
        if (it->getPort() == hand[fd].Get_port() && it->getHost() == hand[fd].Get_host())
        {

            if (it->getAutoindex() == true)
                return true;
        }
    }
    return false;
}

bool server::CheckLocIndex_file(int fd)
{
    std::vector<Server_storage>::iterator it = serv.getServers().begin();
    for (; it != serv.getServers().end(); it++)
    {
        if (it->getPort() == hand[fd].Get_port() && it->getHost() == hand[fd].Get_host())
        {
            for (std::vector<Location_storage>::iterator itr = it->_locations.begin(); itr != it->_locations.end(); itr++)
            {
                if (GetLocationPath(fd) == itr->getLocaPath())
                {
                    if (!itr->getLocaIndex().empty())
                    {
                        hand[fd].Index_file = itr->getLocaIndex();
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

bool server::CheckServIndex_file(int fd)
{
    std::vector<Server_storage>::iterator it = serv.getServers().begin();
    for (; it != serv.getServers().end(); it++)
    {
        if (it->getPort() == hand[fd].Get_port() && it->getHost() == hand[fd].Get_host())
        {

            if (!it->getIndex().empty())
                return true;
        }
    }
    return false;
}
