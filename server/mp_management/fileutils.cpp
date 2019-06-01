#include "fileutils.h"
#include "error_handler.h"

#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

//==============================================================================
//
//==============================================================================
ssize_t getFileSize(const char *filepath) {
    struct stat attr;
    if (stat(filepath, &attr) < 0) {
	fprintf_mp(stderr, "get file stat\r\n");
	return -1;
    }
    return attr.st_size;
}

//==============================================================================
//
//==============================================================================
int getFileCreationTime(const char* filepath, char *dest, size_t dest_len) {
    struct stat attr;
    stat(filepath, &attr);
    const char *time_fmt = "%a, %d %b %Y %T %z";
    return strftime(dest, dest_len, time_fmt, gmtime(&(attr.st_ctime)));
}

//==============================================================================
//
//==============================================================================
const char* getFileExtension(const char* filepath) {
    const char *dot = strrchr(filepath, '.');
    if (!dot || dot == filepath) return "";
    return dot + 1;
}
