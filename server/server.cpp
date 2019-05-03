#include "server.h"


#include <iostream>
#include <sys/socket.h>

//------------------------------------------------------------------------------

constexpr HttpServer::request_t HttpServer::RequestHandlers[];

//==============================================================================
//
//==============================================================================
int HttpServer::handleClientConection(int fd) {
    int size = recv(fd, m_request_buf.get(), MAX_REQUEST_SIZE, MSG_NOSIGNAL);
    if (size > 0) { /* We read some data */
	/* Search the appropriate handler */
	request_t handler = {NULL, NULL};
	int idx = 0;
	while ((handler = HttpServer::RequestHandlers[idx]).name != NULL) {
	    if (strncmp(handler.name, m_request_buf.get(), strlen(handler.name)) == 0) {
		break;
	    }
	}

	if (handler.name && handler.fn) {
	    if ((this->*(handler.fn))(m_request_buf.get()) < 0) {
		fprintf(stderr, "Error handling request \"%s\"!", handler.name);
	    } else {
		const size_t answer_size = m_answer_str.size();
		ssize_t size = send(fd, m_answer_str.c_str(), answer_size, MSG_NOSIGNAL);
		if (size < 0) {
		    perror("send answer");
		    return -1;
		}
	    }
	} else {
	    printf("Can\'t recognize http request!\r\n");
	}
    } else if (size < 0) {
	perror("recv");
	return -1;
    } else {
	/* socket was closed by client */
    }
    return 0;
}

//==============================================================================
//
//==============================================================================
int HttpServer::onGET(char *request) {

    if(!request) return -1;

    char *pch = strtok(request, "\r\n");

    while(pch) {

    }

    while(pch) {
	pch = strtok(NULL, "\r\n");
    }


    printf("GET handler is here!\r\n");
    fflush(stdout);
    return 0;
}

#if 0





const char *ANSWER_OK	    = "HTTP/1.0 200 OK\r\n";
const char *ANSWER_NOTFOUND = "HTTP/1.0 404 Not Found\r\n";

const char *INTERNAL_ERROR_BODY =   "<html><head></head><body>"
				    "<h1> 404 </h1>"
				    "<h2> Requested page not found! </h2>"
				    "</body></html>";


const char *SERVER_HTTP_VERSION = "HTTP/1.0";
const char *SERVER_NAME		= "@serg3vik training server@";
const char *SERVER_POWERED_BY	= "Black magic & obscene expressions";

char test_request[] =
    "GET / HTTP/1.1\r\n"
    "Host: 127.0.0.1:8888\r\n"
    "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0\r\n"
    "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3\r\n"
    "Accept-Encoding: gzip, deflate\r\n"
    "Connection: keep-alive\r\n"
    "Upgrade-Insecure-Requests: 1\r\n";

enum http_req_type_t {INVALID_REQUEST, GET, POST, HEAD, DELETE}; // To be continued...

struct http_header_t {
    const char *name;
    const char *value;
};

struct http_request_t {
    http_req_type_t type;
    const char *root;
    http_header_t headers[];
};


char TX_Buffer[1024] = {0};

//==============================================================================
//
//==============================================================================
static const char* currentTime() {
    time_t t = time(NULL);
    struct tm loctm = *localtime(&t);
    const char *time_fmt = "%a, %d %b %Y %T %z";
    static char timebuf[64] = {0};
    strftime(timebuf, 64, time_fmt, &loctm);
    return timebuf;
}

//==============================================================================
//
//==============================================================================

/*
HTTP/1.1 200 OK
Date: Wed, 11 Feb 2009 11:20:59 GMT
Server: Apache
X-Powered-By: PHP/5.2.4-2ubuntu5wm1
Last-Modified: Wed, 11 Feb 2009 11:20:59 GMT
Content-Language: ru
Content-Type: text/html; charset=utf-8
Content-Length: 1234
Connection: close
(пустая строка)
(запрошенная страница в HTML)
*/
static int onRequest_GET(const char *url, const char *headers) {
    if (!url) return -1;
    char buf[PATH_MAX] = {0};
    char *root_dir = getcwd(buf, PATH_MAX);
    /* If URL is just "/", it should be treaten as "/index.html" */
    if (strcmp("/", url) == 0) {
	url = "/index.html";
    }
    strncat(root_dir, url, PATH_MAX);


    /* Trying to open the file for reading */
    FILE *requested = fopen(root_dir, "r");
    /*HTTP/1.1 404 Not Found
    Date: Sun, 18 Oct 2012 10:36:20 GMT
    Server: Apache/2.2.14 (Win32)
    Content-Length: 230
    Connection: Closed
    Content-Type: text/html; charset=iso-8859-1*/
    if (requested) {

    } else {

	int offset = 0;
	offset += sprintf(TX_Buffer + offset, "%s 404 Not Found\r\n", SERVER_HTTP_VERSION);
	offset += sprintf(TX_Buffer + offset, "Date: %s\r\n", currentTime());
	offset += sprintf(TX_Buffer + offset, "Server: %s\r\n", SERVER_NAME);
	offset += sprintf(TX_Buffer + offset, "X-Powered-By: %s\r\n", SERVER_POWERED_BY);
	offset += sprintf(TX_Buffer + offset, "Content-Length: %d\r\n", strlen(error404));
	offset += sprintf(TX_Buffer + offset, "Connection: Closed\r\n");
	offset += sprintf(TX_Buffer + offset, "Connection-Type: %s; charset=%s\r\n", "text/html", "utf-8");
	offset += sprintf(TX_Buffer + offset, "\r\n");
	offset += sprintf(TX_Buffer + offset, "%s\r\n", error404);
//	"";
    }

    return 0;
}

//==============================================================================
//
//==============================================================================
static int handleHttpRequest(char *raw_buffer) {
    if (!raw_buffer) return -1;


    char *type = strtok(raw_buffer, " ");
    char *url  = strtok(NULL, " ");
    char *ver  = strtok(NULL, "\r\n");

    printf("Type: %s\nURL: %s\nHTTP: %s\n", type, url, ver);

    char *headers = strtok(NULL, "\r\n");

    if (strncmp(type, "GET", strlen("GET")) == 0) {
	/* GET request */
	return onRequest_GET(url, headers);
    }
    return 0;
}
#endif
