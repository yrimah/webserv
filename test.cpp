#include <iostream>

void delete_spaces(std::string &_file)
{
    std::string::size_type _start = 0;
    std::string::size_type _end = _file.size() - 1;

    while (_file[_start] && isspace(_file[_start]))
        _start++;
    while (_end != _start && isspace(_file[_end]))
        _end--;
    _file = _file.substr(_start, _end);
}

int main()
{

    std::string test = "           server       {";
    delete_spaces(test);
    std::cout << test << std::endl;
    return (0);
}