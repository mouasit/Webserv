#include "response.hpp"

int main(){
    request my_request;
    Header response_header;
    my_request = fill_request(my_request);

    if(!is_req_well_formed(my_request,response_header))
    {
        
    }
    else{
        std::cout << response_header.status.first << " : " << response_header.status.second << std::endl;
    }
}