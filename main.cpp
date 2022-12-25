#include "response.hpp"

int main(int argc, char **argv)
{
    request my_request;

    my_request.method = "GET";
    my_request.host = "127.0.0.1";
    my_request.uri = "/index.html";
    my_request.body = "";
    
    std::vector<ServerData>	cData;

	if (parseConfigFile(argc, argv, cData) == -1)
		return (EXIT_FAILURE);

    handle_response(cData[0],my_request);
    return (0);
}