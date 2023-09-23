#ifndef CONF_PARSER_HPP
# define CONF_PARSER_HPP

# include <iostream>
# include <vector>

typedef std::vector<std::string> storage;      

class Conf_parser
{
    private:
        int servers_nbr;
        storage block_conf;

    public:
        Conf_parser();
        ~Conf_parser();

        void store_server(std::string _file);
        void extract_server_blocks(std::string _file);

        void delete_spaces(std::string &_file);
        std::string first_word(std::string::size_type _start, std::string _file);

        std::string::size_type begin_serv(std::string::size_type _start, std::string _file);
        std::string::size_type end_serv(std::string::size_type _start, std::string _file);


        size_t findStartServer (size_t start, std::string &content);
        size_t findEndServer (size_t start, std::string &content);
        int getServers_nbr() const;

        class OutOfServerBlocks : public std::exception
        {
            public:
                virtual const char * what() const throw()
                {
                    return ("Invalid file: charachters out of server block");
                }
        };

        class ErrorEncountered : public std::exception
        {
            public:
                virtual const char * what() const throw()
                {
                    return ("Error Encountered during parsing");
                }
        };
};

#endif