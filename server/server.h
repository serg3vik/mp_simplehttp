#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include <iostream>
#include <memory>
#include <functional>

#include <sys/socket.h>
#include <sys/types.h>

#if 0
char test_request[] =
    "GET / HTTP/1.1\r\n"
    "Host: 127.0.0.1:8888\r\n"
    "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0\r\n"
    "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3\r\n"
    "Accept-Encoding: gzip, deflate\r\n"
    "Connection: keep-alive\r\n"
    "Upgrade-Insecure-Requests: 1\r\n";
#endif

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
    static const size_t MAX_REQUEST_SIZE     = 64 * 1024;
    static const size_t MAX_GET_REQUEST_SIZE = 8 * 1024;
    static const size_t MAX_URL_SIZE	     = 255;

public:
    struct request_t {
	const char	*name;
	request_fn	fn;
    };

public:
    HttpServer() :
    m_request_buf(new char[MAX_REQUEST_SIZE])
    {
    }

    //==============================================================================
    //
    //==============================================================================
    int httpHandlerGET(char *request) {
	printf("GET handler is here!\r\n");
	fflush(stdout);
	return 0;
    }

    //==============================================================================
    //
    //==============================================================================
    int handleClientConection(int fd);

    int handleRawRequest(const std::string &request);
    const std::string& answer();

private:
    std::unique_ptr<char> m_request_buf;
    std::string m_answer_str;

    constexpr static HttpServer::request_t RequestHandlers[] = {
      { "GET"	,   &HttpServer::httpHandlerGET	}
    , { nullptr ,   nullptr				}};

};



#endif // SERVER_H
