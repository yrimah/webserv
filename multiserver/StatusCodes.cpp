#include "../incs/parse_config/StatusCodes.hpp"

StatusCodes::StatusCodes(){
    OK_200 = "HTTP/1.1 200 ok\r\n";
    NotFond_404 = "HTTP/1.1 404 not fond\r\n";
    Forbidden_403 = "HTTP/1.1 403 forbidden\r\n";
    NoContent_204 = "HTTP/1.1 204 No Content\r\n\r\n";
    Method_NAllowed_405 = "HTTP/1.1 405 Method Not Allowed\r\n\r\n";
}

StatusCodes::~StatusCodes(){}
