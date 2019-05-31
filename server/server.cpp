#include <iostream>
#include <sstream>
#include <ios>

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <limits.h>

#include "server.h"
#include "http_error.h"
#include "fileutils.h"
#include "error_handler.h"

//------------------------------------------------------------------------------
extern const char *RootPath;

//------------------------------------------------------------------------------

char TestRequest[] =
    "GET / HTTP/1.1\r\n"
    "Host: 127.0.0.1:8888\r\n"
    "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:60.0) Gecko/20100101 Firefox/60.0\r\n"
    "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0\r\n"
    "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3\r\n"
    "Accept-Encoding: gzip, deflate\r\n"
    "Connection: keep-alive\r\n"
    "Upgrade-Insecure-Requests: 1\r\n";

//------------------------------------------------------------------------------

constexpr HttpServer::request_t HttpServer::RequestHandlers[];

//------------------------------------------------------------------------------
std::unordered_map<std::string, std::string> HttpServer::MimeTypes = {
      std::make_pair("html", "text/html")
    , std::make_pair("htm",  "text/html")
    , std::make_pair("jpeg", "image/jpeg")
    , std::make_pair("jpg",  "image/jpeg")
    , std::make_pair("js",   "document/javascript")
    , std::make_pair("css",  "text/css")
    , std::make_pair("ico",  "image/x-icon")
    /* And so on ... */
};

//------------------------------------------------------------------------------

const char *TextFileTypes[] = {"html", "htm", "css", "js", "txt", NULL};

//------------------------------------------------------------------------------

const char *ANSWER_OK	    = "HTTP/1.0 200 OK";
const char *ANSWER_NOTFOUND = "HTTP/1.0 404 Not Found";

const char *SERVER_HTTP_VERSION = "HTTP/1.0";
const char *SERVER_NAME		= "@serg3vik training server@";
const char *SERVER_POWERED_BY	= "Black magic & obscene expressions";



//==============================================================================
// TODO: move it to separate file
//==============================================================================
static int getCurrentTime(char *dest, size_t dest_len) {
    time_t t = time(NULL);
    struct tm loctm = *localtime(&t);
    const char *time_fmt = "%a, %d %b %Y %T %z";
    return strftime(dest, dest_len, time_fmt, &loctm);
}


//==============================================================================
//
//==============================================================================
HttpServer::HttpServer() :
    m_request_buf(new char[MAX_REQUEST_SIZE]),
    m_answer_filebuf(new uint8_t[ANSWER_FILEBUF_SIZE]),
    m_answer_ss(std::string()),
    m_active_socket(-1),
    m_www_root(std::string())
    {
	m_server_headers["Server: "]	    = SERVER_NAME;
	m_server_headers["X-Powered-By: "]  = SERVER_POWERED_BY;
	m_server_headers["Connection: "]    = "close";

	m_server_headers["Date: "]	    = "";
	m_server_headers["Last-Modified: "] = "";
	m_server_headers["Content-Type: "]  = "";
	m_server_headers["Content-Length: "] = "";
    }

//==============================================================================
//
//==============================================================================
int HttpServer::handleClientConection(int fd) {
    m_active_socket = fd;
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
	    /* clear the output buffer first! */
	    m_answer_ss.str(std::string());
	    /* set root file path */
	    m_www_root = std::string(RootPath);

	    if ((this->*(handler.fn))(m_request_buf.get()) < 0) {
		fprintf_mp(stderr, "Error handling request!");
	    } else {
		/* relocated to request handler */
//		const size_t answer_size = m_answer_ss.str().size();
//		ssize_t size = send(fd, m_answer_ss.str().c_str(), answer_size, MSG_NOSIGNAL);
//		if (size < 0) {
//		    perror("send answer");
//		    return -1;
//		}
	    }
	} else {
//	    printf("Can\'t recognize http request!\r\n");
	}
    } else if (size < 0) {
	fprintf_mp(stderr, "recv");
	return -1;
    } else {
	fprintf_mp(stderr, "socket was closed by client");
//	fflush(stdout);
	/* socket was closed by client */
    }
    return 0;
}

//==============================================================================
//
//==============================================================================
int HttpServer::onGET(char *request) {

    if(!request) return -1;

    char *type = strtok(request, " ");	    // request type
    char *url  = strtok(NULL, " ");	    // URL
    char *http_ver = strtok(NULL, " \r\n"); // HTTP standard version

    fprintf_mp(stdout, "GET handler is here!");

//    printf("GET handler is here! [%s %s %s]\r\n", type, url, http_ver);
//    fflush(stdout);

    /* Reading headers */
    #if 0 /* Don't care on GET request */
    char *pch = strtok(http_ver, "/r/n");
    while(pch) {
	pch = strtok(NULL, "/r/n");
	// TODO: parse interesting headers
    }
    #endif
    if (strncmp(url, "/", 2) == 0) url = "/index.html";
    std::string filepath = m_www_root + url;


    /* Fill out the common headers independent on file existing */

    char datetime_str[32];
    if (getCurrentTime(datetime_str, 32) < 0) {
	fprintf_mp(stderr, "getCurrentTime\n");
	return -1;
    }

    m_server_headers["Date: "] = std::string(datetime_str);

    const char *status = ANSWER_OK;

    char real_filepath[PATH_MAX];
    FILE *f = NULL;

    /* Check if the requested file exists */
    if( access( filepath.c_str(), F_OK ) != -1 ) {
	if (realpath(filepath.c_str(), real_filepath) == NULL) {
	    fprintf_mp(stderr, "realpath");
	    return -1;
	}

	f = fopen(real_filepath, "rb");
	fprintf_mp(stderr, "File found!");// [%s]\r\n", real_filepath);
//	fflush(stdout);
    } else {
	fprintf_mp(stderr, "File NOT found!\r\n");
//	fflush(stdout);

    }

    // TODO: Make separate handlers for ALL errors!
    // for ex.	errorHandler404(int sock);
    //		errorHandler500(int sock);


    /* Headers */
    if (f) {


	ssize_t filesize = getFileSize(real_filepath);
	if (filesize < 0) {
	    fprintf_mp(stderr, "getFileSize");
	    return -1;
	}
	char filecreatetime_str[32];
	getFileCreationTime(real_filepath, filecreatetime_str, 32);

	m_server_headers["Last-Modified: "] = std::string(filecreatetime_str);
	m_server_headers["Content-Type: "] = MimeTypes.at(std::string(getFileExtension(real_filepath)));
	m_server_headers["Content-Length: "] = std::to_string(filesize);

    } else {
	m_server_headers["Content-Length: "] = DefaultError_404.size();
	m_server_headers["Content-Type "] = std::string("text/html");
    }


    m_answer_ss << status << "\r\n";

    for (auto hdr : m_server_headers) {
	m_answer_ss << hdr.first << hdr.second << "\r\n";
    }
    m_answer_ss << "\r\n";

    if (send(m_active_socket, m_answer_ss.str().c_str() , m_answer_ss.str().size(), MSG_NOSIGNAL) < 0) {
	fprintf_mp(stderr, "send answer headers");
	return -1;
    }

    if (f) {
	ssize_t read_size = 0;
	while ((read_size = fread(m_answer_filebuf.get(), sizeof(m_answer_filebuf[0]), ANSWER_FILEBUF_SIZE, f )) > 0) {
	    if (send(m_active_socket, m_answer_filebuf.get(), read_size, MSG_NOSIGNAL) < 0) {
		fprintf_mp(stderr, "send answer file");
		return -1;
	    }
//	    printf(" %d bytes sent to socket\r\n", read_size);
//	    fflush(stdout);
	}
    } else {
	if (send(m_active_socket, DefaultError_404.c_str(), DefaultError_404.size(), MSG_NOSIGNAL) < 0) {
	    fprintf_mp(stderr, "send answer file");
	    return -1;
	}

    }

    return 0;
}

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
