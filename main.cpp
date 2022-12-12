#include "response.hpp"

int main(){
    request my_request;
    config config_file;
    Header response_header;

    my_request = fill_request(my_request);
    config_file = fill_config();
    if(!is_req_well_formed(my_request,response_header))
    {
        if(!check_location(my_request, config_file.root, response_header))
        {
            std::cout << "GET" << std::endl;
        }
    }
    std::cout << response_header.status.first << " : " << response_header.status.second << std::endl;
}