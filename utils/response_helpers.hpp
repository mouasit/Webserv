#ifndef RESPONSE_HELPERS_HPP
#define RESPONSE_HELPERS_HPP

#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <dirent.h>
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
    std::map<std::string,std::string> content_types;
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

std::map<std::string,std::string> fill_content_types(std::map<std::string,std::string> content_types)
{
    content_types["html"] = "text/html";
	content_types["htm"] = "text/html";
	content_types["shtml"] = "text/html";
	content_types["css"] = "text/css";
	content_types["xml"] = "text/css";
	content_types["gif"]= "image/gif";
	content_types["jpeg"]= "image/jpeg";
	content_types["jpg"]= "image/jpeg";
	content_types["png"]= "image/png";
	content_types["js"]= "application/javascript";
	content_types["atom"]= "application/atom+xml";
	content_types["rss"]= "application/rss+xml";
	
	content_types["mml"]= "text/mathml";
	content_types["txt"]= "text/plain";
	content_types["jad"]= "text/vnd.sun.j2me.app-descriptor";
	content_types["wml"]= "text/vnd.wap.wml";
	content_types["htc"]= "text/x-component";
	
	content_types["png"]= "image/png";
	content_types["tif"]= "image/tiff";
	content_types["tiff"]= "image/tiff";
	content_types["wbmp"]= "image/vnd.wap.wbmp";
	content_types["ico"]= "image/x-icon";
	content_types["jng"]= "image/x-jng";
	content_types["bmp"]= "image/x-ms-bmp";
	content_types["svg"]= "image/svg+xml";
	content_types["svgz"]= "image/svg+xml";
	content_types["webp"]= "image/webp";

	content_types["woff"] = "application/font-woff";
	content_types["jar"] = "application/java-archive";
	content_types["war"] = "application/java-archive";
	content_types["ear"] = "application/java-archive";
	content_types["json"] = "application/json";
	content_types["hqx"] = "application/mac-binhex40";
	content_types["doc"] = "application/msword";
	content_types["pdf"] = "application/pdf";
	content_types["ps"] = "application/postscript";
	content_types["eps"] = "application/postscript";
	content_types["ai"] = "application/postscript";
	content_types["rtf"] = "application/rtf";
	content_types["m3u8"] = "application/vnd.apple.mpegurl";
	content_types["xls"] = "application/vnd.ms-excel";
	content_types["eot"] = "application/vnd.ms-fontobject";
	content_types["ppt"] = "application/vnd.ms-powerpoint";
	content_types["wmlc"] = "application/vnd.wap.wmlc";
	content_types["kml"] = "application/vnd.google-earth.kml+xml";
	content_types["kmz"] = "application/vnd.google-earth.kmz";
	content_types["7z"] = "application/x-7z-compressed";
	content_types["cco"] = "application/x-cocoa";
	content_types["jardiff"] = "application/x-java-archive-diff";
	content_types["jnlp"] = "application/x-java-jnlp-file";
	content_types["run"] = "application/x-makeself";
	content_types["pl"] = "application/x-perl";
	content_types["pm"] = "application/x-perl";
	content_types["prc"] = "application/x-pilot";
	content_types["pdb"] = "application/x-pilot";
	content_types["rar"] = "application/x-rar-compressed";
	content_types["rpm"] = "application/x-redhat-package-manager";
	content_types["sea"] = "application/x-sea";
	content_types["swf"] = "application/x-shockwave-flash";
	content_types["sit"] = "application/x-stuffit";
	content_types["tcl"] = "application/x-tcl";
	content_types["tk"] = "application/x-tcl";
	content_types["der"] = "application/x-x509-ca-cert";
	content_types["pem"] = "application/x-x509-ca-cert";
	content_types["cert"] = "application/x-x509-ca-cert";
	content_types["xpi"] = "application/x-xpinstall";
	content_types["xhtml"] = "application/xhtml+xml";
	content_types["xspf"] = "application/xspf+xml";
	content_types["zip"] = "application/zip";

	content_types["bin"] = "application/octet-stream";
	content_types["exe"] = "application/octet-stream";
	content_types["dll"] = "application/octet-stream";
	content_types["deb"] = "application/octet-stream";
	content_types["dmg"] = "application/octet-stream";
	content_types["iso"] = "application/octet-stream";
	content_types["img"] = "application/octet-stream";
	content_types["msi"] = "application/octet-stream";
	content_types["msp"] = "application/octet-stream";
	content_types["msm"] = "application/octet-stream";

	content_types["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	content_types["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	content_types["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";

	content_types["mid"] = "audio/midi";
	content_types["midi"] = "audio/midi";
	content_types["kar"] = "audio/midi";
	content_types["mp3"] = "audio/mpeg";
	content_types["ogg"] = "audio/ogg";
	content_types["m4a"] = "audio/x-m4a";
	content_types["ra"] = "audio/x-realaudio";

	content_types["3gpp"] = "video/3gpp";
	content_types["3gp"] = "video/3gpp";
	content_types["ts"] = "video/mp2t";
	content_types["mp4"] = "video/mp4";
	content_types["mpeg"] = "video/mpeg";
	content_types["mpg"] = "video/mpeg";
	content_types["mov"] = "video/quicktime";
	content_types["webm"] = "video/webm";
	content_types["flv"] = "video/x-flv";
	content_types["m4v"] = "video/x-m4v";
	content_types["mng"] = "video/x-mng";
	content_types["asx"] = "video/x-ms-asf";
	content_types["asf"] = "video/x-ms-asf";
	content_types["wmv"] = "video/x-ms-wmv";
	content_types["avi"] = "video/x-msvideo";

    return content_types;
}

code_status  fill_status(code_status status)
{
    status.message_status = fill_message_status(status.message_status);
    status.error_pages = fill_error_pages(status.error_pages);
    status.content_types = fill_content_types(status.content_types);
    return status;
}

std::string get_content_type(std::string path_file, std::map<std::string,std::string> content_types)
{
    std::string extention;

    extention = path_file.substr(path_file.find_last_of('.') + 1);
    if(content_types.count(extention))
        return(content_types[extention]);
    return "application/octet-stream";
}

std::string get_body(std::string path_file)
{
    std::ifstream file(path_file);
    std::string body;



    if(file.is_open())
    {
        while (file)
            body += file.get();
    }
    body[body.length() - 1] = '\0';
    return body;
}

std::string get_body_error_page(int code, std::string message)
{
	std::string body = "<!DOCTYPE html>\n"\
"<html lang=\"en\">\n"\
"<head>\n"\
"    <meta charset=\"UTF-8\">\n"\
"    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"\
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"\
"    <title>" + std::to_string(code) + " " + message + "</title>\n"\
"    <style>\n"\
"        h1{text-align: center;}\n"\
"    </style>\n"\
"</head>\n"\
"<body>\n"\
"    <h1>" + std::to_string(code) + " " + message +"</h1>\n"\
"    <hr>\n"\
"</body>\n"\
"</html>";
	return body;
}

void set_response(int code, response_data &response_data, code_status status, std::string file_request = "")
{
	std::string response;

    /* body */
	if(file_request.length() == 0)
    	response_data.body = get_body_error_page(code,status.message_status[code]);
	else
		response_data.body = get_body(file_request);

    /* start line */

    response_data.start_line.host = "HTTP/1.1";
    response_data.start_line.status = std::to_string(code) + " " + status.message_status[code];

    /* headers */

    response_data.headers.content_length = std::to_string(response_data.body.length());
    response_data.headers.content_type = get_content_type(status.error_pages[code],status.content_types);

	response+= response_data.start_line.host + " " + response_data.start_line.status + '\r' + '\n' + 
			   "Content-Length: " + response_data.headers.content_length + '\r' + '\n' + "Content-Type: " + response_data.headers.content_type + 
			   '\r' + '\n' + '\n' + response_data.body + '\r' + '\n' + '\r' + '\n';
	std::cout << response;

}

bool is_directory(const char *uri)
{
    struct stat buff;
    
    lstat(uri,&buff);
    if(S_ISDIR(buff.st_mode))
        return true;
    return false;
}
bool location_match(const char *uri,response_data &response_data, code_status status)
{

	struct stat buff;
	if(lstat(uri,&buff) == -1)
	{
		set_response(404,response_data,status);
		return false;
	}
	return true;
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

std::string get_autoindex_directory(std::string root_path)
{
	std::string body;
	DIR *d;
    struct dirent *dir;

    d = opendir("./");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }

	body = "<!DOCTYPE html>\n"\
"<html lang=\"en\">\n"\
"<head>\n"\
"    <meta charset=\"UTF-8\">\n"\
"    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"\
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"\
"    <title>Auto Index</title>\n"\
"    <style>\n"\
"        h1{text-align: center;}\n"\
"    </style>\n"\
"</head>\n"\
"<body>\n"\
"    <a href=\"#\">default-pages</a>\n"\
"</body>\n"\
"</html>";

return body;
}

#endif