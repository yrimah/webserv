#pragma once

#include <iostream>

class StatusCodes
{
    public :
        std::string OK_200;
        std::string NotFond_404;
        std::string Forbidden_403;
        std::string NoContent_204;
        std::string Method_NAllowed_405;
    public :
        StatusCodes();
        ~StatusCodes();
};

