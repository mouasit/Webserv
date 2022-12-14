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

            }
        }
        else{

        }
    }
    std::cout << response_header.status.first << " : " << response_header.status.second << std::endl;
}