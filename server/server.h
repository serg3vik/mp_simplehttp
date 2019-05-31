#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include <iostream>
#include <sstream>
#include <memory>
#include <unordered_map>

#include <sys/socket.h>
#include <sys/types.h>

extern char TestRequest[];

//------------------------------------------------------------------------------
#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))
//------------------------------------------------------------------------------

class HttpServer;
//------------------------------------------------------------------------------
typedef int (HttpServer::*request_fn)(char*);
//------------------------------------------------------------------------------

//==============================================================================
//
//==============================================================================
class HttpServer
{
    static const size_t ANSWER_FILEBUF_SIZE  = 32 * 1024;
    static const size_t MAX_REQUEST_SIZE     = 64 * 1024;
    static const size_t MAX_GET_REQUEST_SIZE = 8 * 1024;
    static const size_t MAX_URL_SIZE	     = 255;

public:
    struct request_t {
	const char	*name;
	request_fn	fn;
    };

public:
    HttpServer();

    int onGET(char *request);

    int handleClientConection(int fd);

    const std::string& answer();

private:
    std::unique_ptr<char[]> m_request_buf;
    std::unique_ptr<uint8_t[]> m_answer_filebuf;
    std::stringstream m_answer_ss;

    int			m_active_socket;

    std::string m_www_root;

    std::unordered_map<std::string, std::string> m_server_headers;

    static std::unordered_map<std::string, std::string> MimeTypes;

    constexpr static HttpServer::request_t RequestHandlers[] = {
      { "GET"	,   &HttpServer::onGET	}
    , { nullptr ,   nullptr				}};

};

//==============================================================================
//
//==============================================================================


#endif // SERVER_H
