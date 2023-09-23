#ifndef LOCATION_STORAGE_HPP
#define LOCATION_STORAGE_HPP

# include "conf_parser.hpp" 

class Location_storage
{
    private:
        std::string loca_path;
		std::string loca_root;
		bool loca_autoindex;
		std::string	loca_index;
		std::vector<int> loca_allowed_methods;
		// std::string	loca_return;
		std::string	loca_alias;
		storage	loca_cgi_path;
		// stotage	loca_cgi_extension;
		unsigned long loca_client_max_body_size;

    public:
        Location_storage();
        ~Location_storage();

        void init_location();
};

#endif