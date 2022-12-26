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
#include "./parseConfigFile/parseConfigFile.hpp"
#include "./helpers.hpp"

class response{
    private:
        bool        is_directory();
        bool        is_slash_in_end();
        bool        index_files();
        bool        post_index_files();
        bool        location_has_cgi();
        bool        post_location_has_cgi();
        bool        is_auto_index();
        bool        support_upload();

        void        fill_content_types();
        std::string get_auto_index_directory();
        std::string get_body_res_page(int code);
        std::string get_body_post(int code);
        std::string get_body(std::string path_file);
        std::string get_content_type(std::string path_file);
    public:
        response(const LocationData &location, request my_request):location(location){
            // fill request.
            this->req = my_request;

            // fill errors.
            message_status.insert(std::make_pair(400,"Bad Request"));
            message_status.insert(std::make_pair(414,"Request-URI Too Long"));
            message_status.insert(std::make_pair(413,"Request Entity Too Large"));
            message_status.insert(std::make_pair(404,"Not Found"));
            message_status.insert(std::make_pair(301,"Moved Permanently"));
            message_status.insert(std::make_pair(405,"Method Not Allowed"));
            message_status.insert(std::make_pair(403,"Forbidden"));
            message_status.insert(std::make_pair(200,"OK"));
            message_status.insert(std::make_pair(201,"Created"));

            //fill content_types.
            fill_content_types();
        };
        ~response(){};

        request                   req;
        std::map<int,std::string> message_status;
        std::map<std::string,std::string> content_types;
        const LocationData                location;
        std::string                 root;

        bool        request_valid(request req, long max_body_size);
        bool        check_location_config_file(std::pair<unsigned short,std::string> redirection);
        bool        method_allowed(std::string method);
        bool        resource_root();
        void        GET_method();
        void        POST_method();

        void        set_response_error(int code);
        void        set_response_permanently(int code,std::string redirection);
        void        set_response_file(int code);
        void        set_response_auto_index(int code,std::string body);
        void        set_response_post(int code);
};


LocationData    get_location(ServerData server, request &my_request);
void            handle_response(ServerData server, request my_request);

#endif