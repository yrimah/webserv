# include "../../incs/cgi_config/cgi_conf.hpp"

Cgi_conf::Cgi_conf()
{
    this->_env = NULL;
    this->_argv = NULL;
    this->status = 0;
    this->path = "";
    this->cgi_id = -1;
}

Cgi_conf::~Cgi_conf()
{
    // if (this->_env)
    // {
    //     for (int i = 0; this->_env[i]; i++)
    //         free(this->_env[i]);
    //     free(this->_env);
    // }

    // if (this->_argv)
    // {
    //     for (int i = 0; this->_argv[i]; i++)
    //         free(this->_argv[i]);
    //     free(this->_argv);
    // }
}

std::string getHeader(std::map<std::string, std::string> headers, std::string key)
{
    for (map_it it = headers.begin(); it != headers.end(); it++)
    {
        if (it->first == key)
            return (it->second);
    }
    return (NULL);
}

void Cgi_conf::initialize_cgi_env(Request requestObj, Loca_it _it)
{
    // std::cout << "NAN\n";
    std::map<std::string, std::string> cgi_execs;

    cgi_execs[".py"] = _it->getLocaCgipath()[0];
    cgi_execs[".php"] = _it->getLocaCgipath()[1];

    std::string ext = this->path.substr(this->path.find("."));

    std::string cgi_exec = "";

    // std::cout << this->path << " :: " << _it->getLocaPath() << " :: " << ext << "\n";
    for (map_it it = cgi_execs.begin(); it != cgi_execs.end(); it++)
    {
        if (ext == it->first)
            cgi_exec = it->second;
    }
    if (cgi_exec.empty())
        throw Cgi_conf::CgiException("Unsupported file extension");

    // std::cout << this->cgi_env["CONTENT_LENGTH"] << "::IT IS\n";

    this->cgi_env["CONTENT_LENGTH"] = requestObj.request_head["content-length"];
    this->cgi_env["CONTENT_TYPE"] = requestObj.request_head["content-type"];
    this->cgi_env["GATEWAY_INTERFACE"] = std::string("CGI/1.1");
    // std::cout << this->cgi_env["GATEWAY_INTERFACE"] << "::IT IS\n";
    this->cgi_env["REMOTE_ADDR"] = requestObj.Host; // those are the same thing
    // this->cgi_env["REMOTE_HOST"] = ; // those are the same thing
    this->cgi_env["REQUEST_METHOD"] = requestObj.method;
    this->cgi_env["HTTP_COOKIE"] = requestObj.request_head["cookie"];
    this->cgi_env["SCRIPT_FILENAME"] = this->path.substr(this->path.find_last_of("/") + 1);
    this->cgi_env["SCRIPT_NAME"] = this->path;
    // std::cout << this->cgi_env["SCRIPT_FILENAME"] << " :: " << this->cgi_env["SCRIPT_NAME"] << "\n";
    // this->cgi_env["SERVER_NAME"] = ;
    this->cgi_env["QUERY_STRING"] = requestObj.query_string;
    // this->cgi_env["PATH_INFO"] = ;
    this->cgi_env["REDIRECT_STATUS"] = "200";
    // this->cgi_env["REQUEST_URI"] = ;
    this->cgi_env["SERVER_PORT"] = requestObj.Port;
    this->cgi_env["SERVER_PROTOCOL"] = std::string("HTTP/1.1");
    // this->cgi_env[""] = ;
    // this->cgi_env[""] = ;
    
    // add the request headers to the map //
    this->_argv = (char **)malloc(sizeof(char *) * 3);
    this->_env = (char **)malloc(sizeof(char *) * (this->cgi_env.size() + 1));

    this->_argv[2] = NULL;
    this->_argv[1] = strdup((char *)this->path.c_str());
    this->_argv[0] = strdup((char *)cgi_exec.c_str());

    map_it it = this->cgi_env.begin();
    for (int i = 0; it != cgi_env.end(); it++, i++)
    {
        std::string value = it->first + "=" + it->second;
        this->_env[i] = strdup(value.c_str());
    }
}

void Cgi_conf::setPath(std::string path)
{
    this->path = path;
}

void Cgi_conf::cgi_executer(int &error)
{
    if (!this->_argv[0] || !this->_argv[1])
	{
		error = 500;
        // std::cout << "1a\n";
		return ;
	}
	if (pipe(_in) < 0)
	{
		error = 500;
        // std::cout << "2a\n";
		return ;
	}
	if (pipe(_out) < 0)
	{
        std::cerr << "Error in pipe()" << std::endl;
		close(_in[0]);
		close(_in[1]);
		error = 500;
        // std::cout << "3a\n";
		return ;
	}
	this->cgi_id = fork();
    // std::cout << cgi_id << "::ID\n";
    if (this->cgi_id < 0)
    {
        // std::cout << "5a\n";
        std::cerr << "Error in fork" << std::endl;
		error = 500;
    }
	else if (this->cgi_id == 0)
	{
		dup2(_in[0], STDIN_FILENO);
		dup2(_out[1], STDOUT_FILENO);
		close(_in[0]);
		close(_in[1]);
		close(_out[0]);
		close(_out[1]);
		if (status = execve(this->_argv[0], this->_argv, this->_env) == -1)
            std::cerr << "Error in execve : " << errno << std::endl;
		exit(status);
	}
	// else if (this->cgi_id > 0;)
    // {
    // }
}


void Cgi_conf::clear()
{
	this->cgi_id = -1;
	this->status = 0;
	this->path = "";
	this->_env = NULL;
	this->_argv = NULL;
	// this->cgi_env.clear();
}
// int main ()
// {
//     Cgi_conf cgi;
//     // cgi.initilize_cgi_env()
// }

/*
AUTH_TYPE=Basic
CONTENT_LENGTH=5188
CONTENT_TYPE=multipart/form-data; boundary=----WebKitFormBoundarySinPzHAITv2F216B
DOCUMENT_ROOT=./
GATEWAY_INTERFACE=CGI/1.1
HTTP_COOKIE=1=1; 2=2; user=hello
PATH_INFO=
PATH_TRANSLATED=.//
QUERY_STRING=
REDIRECT_STATUS=200
REMOTE_ADDR=127.0.0.1:8002
REQUEST_METHOD=POST
REQUEST_URI=/cgi-bin/upload.py
SCRIPT_FILENAME=upload.py
SCRIPT_NAME=cgi-bin/upload.py
SERVER_NAME=127.0.0.1
SERVER_PORT=8080
SERVER_PROTOCOL=HTTP/1.1
SERVER_SOFTWARE=INFINITY
*/

/*
AUTH_TYPE=Basic
CONTENT_LENGTH=
CONTENT_TYPE=
DOCUMENT_ROOT=./
GATEWAY_INTERFACE=CGI/1.1
HTTP_COOKIE=1=1; 2=2; SID=ff7896505c3ee175444a59be5e4fd1db7aea7da3
PATH_INFO=
PATH_TRANSLATED=.//
QUERY_STRING=
REDIRECT_STATUS=200
REMOTE_ADDR=127.0.0.1:8002
REQUEST_METHOD=GET
REQUEST_URI=/cgi-bin/acc.py
SCRIPT_FILENAME=acc.py
SCRIPT_NAME=cgi-bin/acc.py
SERVER_NAME=127.0.0.1
SERVER_PORT=8080
SERVER_PROTOCOL=HTTP/1.1
SERVER_SOFTWARE=INFINITY
*/

// Cgi_conf::cgi_env_seter()//Request &oRequest)
// {
//     if (method == "POST")// post method
//     {
//         this->["CONTENT_TYPE"] = ;
//         this->["CONTENT_LENGTH"] = ;
//     }
//     this->_env["GATEWAY_INTERFACE"] = "CGI/1.1";
//     this->_env["SERVER_NAME"] = ;
//     this->_env["SERVER_PORT"] = ;
//     this->_env["REQUEST_METHOD"] = ;
//     this->_env["REQUEST_URI"] = ;
//     this->_env["SCRIPT_NAME"] = ;
//     this->_env["SCRIPT_FILENAME"] = ;
//     this->_env["PATH_INFO"] = ;
//     this->_env["PATH_TRANSLATED"] = ;
//     this->_env["SERVER_PROTOCOL"] = "HTTP/1.1";
//     this->_env["REDIRECT_STATUS"] = ;
// }

// Cgi_conf::cgi_executer()
// {
    
// }

/*

GATEWAY_INTERFACE: The version of the CGI protocol. Typically set to "CGI/1.1".
SERVER_NAME: The hostname or IP address of the server.
SERVER_PORT: The port on which the server is listening (e.g., 80 for HTTP).
REQUEST_METHOD: The HTTP request method, such as "GET", "POST", etc.
SCRIPT_NAME: The virtual path to the script being executed.
SCRIPT_FILENAME: The filesystem path to the script being executed.
PATH_INFO: The path component of the URL following the script name.
PATH_TRANSLATED: The server's internal filesystem path after any alias and translation handling.
REQUEST_URI: The full original request URI.
SERVER_PROTOCOL: The version of the protocol the client used, typically "HTTP/1.1".
REDIRECT_STATUS: The HTTP status code returned to the client.

*/