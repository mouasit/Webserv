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

typedef struct code_status{
    std::map<int,std::string> message_status;
    std::map<int,std::string> error_pages;
}code_status;

std::map<int,std::string> fill_message_status(std::map<int,std::string> message_status)
{
    message_status.insert(std::make_pair(200,"OK"));
    message_status.insert(std::make_pair(404,"Not Found"));
    message_status.insert(std::make_pair(301,"Moved Permanently"));
    message_status.insert(std::make_pair(403,"Forbidden"));
    return message_status;
}

std::map<int, std::string> fill_error_pages(std::map<int,std::string> error_pages)
{
    error_pages.insert(std::make_pair(404,"./error_pages/404.html"));
    error_pages.insert(std::make_pair(301,"./error_pages/301.html"));
    error_pages.insert(std::make_pair(403,"./error_pages/403.html"));
    return error_pages;
}

code_status  fill_status(code_status status)
{
    status.message_status = fill_message_status(status.message_status);
    status.error_pages = fill_error_pages(status.error_pages);
    return status;
}

void set_response(int code, response_data &response_data, code_status status)
{
    response_data.start_line.host = "HTTP/1.1";
    response_data.start_line.status = std::to_string(code) + " " + status.message_status[code];

    std::cout << status.error_pages[code] << std::endl;
}

bool is_directory(const char *uri)
{
    struct stat buff;
    
    lstat(uri,&buff);
    if(S_ISDIR(buff.st_mode))
        return true;
    return false;
}

bool is_slash_in_end(std::string uri, response_data &response_data,code_status status)
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

bool is_auto_index(std::string autoIndex, response_data &response_data, code_status status)
{
    if(autoIndex == "on")
        return true;
    set_response(403,response_data,status);
    return false;
}

#endif