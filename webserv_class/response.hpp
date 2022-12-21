#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <vector>
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
            std::string root;
            std::string autoindex;
	        std::vector<std::string> index;
	        std::pair<std::string, std::string> redirection;
            Location server_location;
        }config_file;
        
        std::string get_root_path(std::string root_path);
        Location    get_location(std::vector<Location> locations);
    public:
        response(std::vector<Location> locations){
            
            // fill request.
            this->req.method = "GET";
            this->req.host = "127.0.0.1";
            this->req.uri = "/";
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
};

#endif