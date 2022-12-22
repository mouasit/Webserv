#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <iostream>
typedef struct request{
    std::string method;
	std::string host;
    std::string uri;
    std::string body;
}request;

#endif 