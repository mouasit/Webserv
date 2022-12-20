#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <map>
#include "../config_file/parser.hpp"
#include "response_helpers.hpp"


my_request fill_request(my_request request){
    request.method = "GET";
    request.host = "127.0.0.1";
    request.uri = "/kapouet/pouic/toto/pouet";
    return request;
}

config fill_config(config newConfig, std::vector<Vserver> config_file,std::string request_uri)
{
    newConfig.root = get_root_path(config_file[0]._rootPath,config_file[0]._locations,request_uri);
    newConfig.autoindex = "on";
    newConfig.redirection.first = config_file[0]._locations[0]._redirection.first;
    newConfig.redirection.second = config_file[0]._locations[0]._redirection.second;
    return newConfig;
}

info fill_data(info &data,std::vector<Vserver> config_file)
{
    data.request = fill_request(data.request);
    data.config_file = fill_config(data.config_file, config_file, data.request.uri);

    data.pages.page_request = "";
    data.pages.string_page_request = "";
    return data;
}


#endif