#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <map>
#include "../config_file/parser.hpp"
#include "response_helpers.hpp"


my_request fill_request(my_request request){
    request.method = "GET";
    request.uri = "/";
    return request;
}

config fill_config(config newConfig, std::vector<Vserver> config_file,std::string request_uri)
{

    newConfig.root = get_root_path(config_file[0]._rootPath,config_file[0]._locations,request_uri);
    // newConfig.index[0] = "index.html";
    // newConfig.index[1] = "about.html";
    newConfig.autoindex = "on";
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