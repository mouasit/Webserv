#include "response.hpp"

int main(){
    request my_request;
    config config_file;
    Header response_header;

    my_request = fill_request(my_request);
    config_file = fill_config();

    if(my_request.method == "GET")
    {
        if(is_directory((config_file.root + my_request.uri).c_str()))
        {
            if(is_slash_in_end(my_request.uri,response_header))
            {
                if(check_index_files(config_file))
                {
                    // location cgi
                }
                else{
                    if(is_auto_index(config_file.autoindex,response_header))
                    {
                        std::cout << "autoindex of the directory" << std::endl;
                        response_header.status.first = 200;
                        response_header.status.second = "OK";
                    }
                }
            }
        }
        else{

        }
    }
    std::cout << response_header.status.first << " : " << response_header.status.second << std::endl;
}