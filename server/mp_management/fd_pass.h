#ifndef FD_PASS_H
#define FD_PASS_H

#include <stdint.h>
#include <stdlib.h>

//------------------------------------------------------------------------------
ssize_t sock_fd_write(int sock, const void *buf, ssize_t buflen, int fd);
ssize_t sock_fd_read(int sock, void *buf, ssize_t bufsize, int *fd);

#endif // FD_PASS_H
