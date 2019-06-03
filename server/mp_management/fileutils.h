#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <stdint.h>
#include <stdlib.h>

ssize_t getFileSize(const char *filepath);
int getFileCreationTime(const char* filepath, char *dest, size_t dest_len);
const char* getFileExtension(const char* filepath);

#endif // FILEUTILS_H
