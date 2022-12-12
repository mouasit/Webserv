#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <iostream>
#include <unistd.h>

typedef struct request{

    std::string method;
    std::string transfer_encoding;
    int content_length;
    std::string uri;

} request;


typedef struct config{

    std::string root;

} config;


typedef struct Header{
    std::pair<int,std::string> status;
} Header;

request fill_request(request my_request){
    my_request.method = "GET";
    my_request.transfer_encoding = "chuncked";
    my_request.content_length = 5;
    my_request.uri = "/index.html";
    return my_request;
}

config fill_config()
{
    config config_file;

    config_file.root = ".";
    return config_file;
}

bool is_req_well_formed(request my_request, Header &response_header)
{
    /* -------------------- Todo list --------------------   
            * 501 : Not Implemented
            * 413 : Request Entity Too Large
    */

    size_t check_allowded =  my_request.uri.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%");
    
    if(check_allowded != std::string::npos)
    {
        response_header.status.first = 400;
        response_header.status.second = "Bad Request";
        return true;
    }
    if(my_request.uri.length() > 2048)
    {
        response_header.status.first = 414;
        response_header.status.second = "Request-URI Too Long";
        return true;
    }
    return false;   
}

bool check_location(request my_request,std::string root,Header &response_header)
{
    int path = access((root + my_request.uri).c_str() , F_OK);
    if (path == -1)
    {
        response_header.status.first = 404;
        response_header.status.second = "Not Found";
        return true;
    }
    return false;
}
#endif