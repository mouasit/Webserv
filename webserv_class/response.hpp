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
        void        fill_content_types();
        std::string get_auto_index_directory();
        std::string get_body_res_page(int code);
        std::string get_body(std::string path_file);
        std::string get_content_type(std::string path_file);
    public:
        response(std::vector<Location> locations){
            
            // fill request.
            this->req.method = "GET";
            this->req.host = "127.0.0.1";
            this->req.uri = "/test/";
            this->req.body = "";

            // fill location.
            this->conf.server_location = get_location(locations);

            // fill errors.
            message_status.insert(std::make_pair(400,"Bad Request"));
            message_status.insert(std::make_pair(414,"Request-URI Too Long"));
            message_status.insert(std::make_pair(413,"Request Entity Too Large"));
            message_status.insert(std::make_pair(404,"Not Found"));
            message_status.insert(std::make_pair(301,"Moved Permanently"));
            message_status.insert(std::make_pair(405,"Method Not Allowed"));
            message_status.insert(std::make_pair(403,"Forbidden"));
            message_status.insert(std::make_pair(200,"OK"));

            //fill content_types.
            fill_content_types();
        };
        
        response(){};
        ~response(){};

        request                   req;
        config_file               conf;
        std::map<int,std::string> message_status;
        std::map<std::string,std::string> content_types;

        bool        request_valid(request req, std::string max_body_size);
        bool        check_location_config_file(bool is_filled, std::pair<std::string,std::string> redirection);
        bool        method_allowed(std::string method);
        void        GET_method(Vserver server, Location location);

        void        set_response_error(int code);
        void        set_response_permanently(int code,std::string redirection);
        void        set_response_file(int code);
        void        set_response_auto_index(int code,std::string body);
};

#endif