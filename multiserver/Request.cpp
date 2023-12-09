#include "../incs/parse_config/Request.hpp"


Request::Request()
{
        Head_send = false;
        indexFile_open = false;
        send_filed = true;
        //
        query_string = "";
}

Request::~Request()
{
}

void Request::read_request(char b[])
{
    //std::cout << b << std::endl;
    std::istringstream s(b);
    std::string read;
    if(method.empty())
    {
        std::getline(s, read, '\n');
        std::istringstream r(read);
        std::getline(r, method, ' ');
        std::getline(r, path, ' ');
        std::getline(r, http_version);
    }
    while (std::getline(s, read, '\n'))
    {
            size_t i = read.find(':');
            if(i != std::string::npos)
            {
                //std::cout << "Here data 3" << std::endl;
                key = read.substr(0, i);
                //std::cout << "Here data 4 : " << read << std::endl;
                value = read.substr(i + 2, read.length() - i);
                //std::cout << "Here data 5" << std::endl;
            }
            else
            {
                value += read;
                //value += "\n";
            }
            value += "\n";
            request_head[key] = value;
    }
}

uint16_t Request::Get_port()
{
    std::map<std::string , std::string>::iterator itr = request_head.find("Host");
    size_t pos = itr->second.find(":");
    std::string port = itr->second.substr(pos + 1, itr->second.length() - pos - 2);
    std::istringstream cast(port);
    uint16_t d;
    if(!(cast>>d))
        throw std::runtime_error("port Error of converting");
    return (d);
}

in_addr_t Request::Get_host()
{
    std::map<std::string , std::string>::iterator itr = request_head.find("Host");
    size_t pos = itr->second.find(":");
    std::string host = itr->second.substr(0, pos);
    if(host == "localhost")
        host = "127.0.0.1";
    std::istringstream cast(host);
    in_addr_t d = inet_addr(host.data());
    return (d);
}