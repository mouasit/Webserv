#ifndef RESPONSE_HELPERS_HPP
#define RESPONSE_HELPERS_HPP

#include <iostream>
#include <sys/stat.h>
#include <map>


typedef struct start_line{
    std::string host;
    std::string status;
}start_line;


typedef struct headers{
    std::string content_length;
    std::string content_type;
} headers;

typedef struct response_data{
    start_line  start_line;
    headers     headers;
    std::string body;
}response_data;

std::map<int,std::string>   fill_status(std::map<int,std::string> status)
{
    status.insert(std::make_pair(200,"OK"));
    status.insert(std::make_pair(404,"Not Found"));
    status.insert(std::make_pair(301,"Moved Permanently"));
    status.insert(std::make_pair(403,"Forbidden"));
    return status;
}

void set_response(int code, response_data &response_data, std::map<int,std::string> status)
{
    response_data.start_line.host = "HTTP/1.1";
    response_data.start_line.status = std::to_string(code) + " " + status[code];
}

bool is_directory(const char *uri)
{
    struct stat buff;
    
    lstat(uri,&buff);
    if(S_ISDIR(buff.st_mode))
        return true;
    return false;
}

bool is_slash_in_end(std::string uri, response_data &response_data,std::map<int,std::string> status)
{
    /* 
        ------------- TODO -------------
            
            - make a 301 redirection to request uri with '/' addeed at the end.
     */

    if(uri[uri.length() - 1] == '/')
        return true;
    set_response(301,response_data,status);
    return false;
}

bool check_index_files(config config_file)
{
        /* 
        ------------- TODO -------------
            
            - check location files in index "if path file not found go to the next file".
     */

    if(sizeof(config_file.index)/sizeof(config_file.index[0]) > 0)
        return true;
    return false;
}

bool location_has_cgi()
{
    return false;
}

bool is_auto_index(std::string autoIndex, response_data &response_data, std::map<int,std::string> status)
{
    if(autoIndex == "on")
        return true;
    set_response(403,response_data,status);
    return false;
}

#endif