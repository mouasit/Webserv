#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
#include <map>
#include <vector>
#include <cstring>
#include <string.h>
#include "./config_file/parser.hpp"

class response{
    private:
        typedef struct request{
            std::string method;
	        std::string host;
            std::string uri;
            std::string body;
        }request;

        typedef struct config_file{
            Location server_location;
            std::string root;
            std::string autoindex;
	        std::vector<std::string> index;
	        std::pair<std::string, std::string> redirection;
        }config_file;
        
        Location    get_location(std::vector<Location> locations);
        void        fill_config(Vserver server,Location location);
        std::string get_root(std::string root, Location location);
        bool        resource_root();
        bool        is_directory();
        bool        is_slash_in_end();
        bool        index_files();
        bool        location_has_cgi();
        bool        is_auto_index();
        std::string get_auto_index_directory();
    public:
        response(std::vector<Location> locations){
            
            // fill request.
            this->req.method = "GET";
            this->req.host = "127.0.0.1";
            this->req.uri = "/test/";
            this->req.body = "";

            
            // fill location.
            this->conf.server_location = get_location(locations);
        };
        
        response(){};
        ~response(){};

        request     req;
        config_file conf;

        bool        request_valid(request req, std::string max_body_size);
        bool        check_location_config_file(bool is_filled, std::pair<std::string,std::string> redirection);
        bool        method_allowed(std::string method);
        void        GET_method(Vserver server, Location location);
};

#endif