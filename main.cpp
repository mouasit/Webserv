#include "response.hpp"

int main()
{
    std::vector<Vserver> config_file;
    config_file = parsingConfigFile("file.config");
    request my_request;
    
    my_request.method = "GET";
    my_request.host = "127.0.0.1";
    my_request.uri = "/test/";
    my_request.body = "";

    handle_response(config_file[0],my_request);

    return (0);
}