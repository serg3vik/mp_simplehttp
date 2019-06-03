#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <string.h>

#include "error_handler.h"

//------------------------------------------------------------------------------
static const uint16_t DEFAULT_LISTENING_PORT = 8888;

//==============================================================================
//
//==============================================================================
ssize_t sock_fd_write(int sock, const void *buf, ssize_t buflen, int fd) {
    ssize_t     size;
    struct msghdr   msg;
    struct iovec    iov;
    union {
        struct cmsghdr  cmsghdr;
        char        control[CMSG_SPACE(sizeof (int))];
    } cmsgu;
    struct cmsghdr  *cmsg;

    iov.iov_base = (void*)buf;
    iov.iov_len = buflen;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    if (fd != -1) {
        msg.msg_control = cmsgu.control;
        msg.msg_controllen = sizeof(cmsgu.control);

        cmsg = CMSG_FIRSTHDR(&msg);
        cmsg->cmsg_len = CMSG_LEN(sizeof (int));
        cmsg->cmsg_level = SOL_SOCKET;
        cmsg->cmsg_type = SCM_RIGHTS;

        printf ("passing fd %d\n", fd);
        *((int *) CMSG_DATA(cmsg)) = fd;
    } else {
        msg.msg_control = NULL;
        msg.msg_controllen = 0;
        printf ("not passing fd\n");
    }

    size = sendmsg(sock, &msg, 0);

    if (size < 0)
        perror ("sendmsg");
    return size;
}

//==============================================================================
//
//==============================================================================
ssize_t sock_fd_read(int sock, void *buf, ssize_t bufsize, int *fd) {
    ssize_t     size;

    if (fd) {
        struct msghdr   msg;
        struct iovec    iov;
        union {
            struct cmsghdr  cmsghdr;
            char        control[CMSG_SPACE(sizeof (int))];
        } cmsgu;
        struct cmsghdr  *cmsg;

        iov.iov_base = buf;
        iov.iov_len = bufsize;

        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        msg.msg_iov = &iov;
        msg.msg_iovlen = 1;
        msg.msg_control = cmsgu.control;
        msg.msg_controllen = sizeof(cmsgu.control);
        size = recvmsg (sock, &msg, 0);
        if (size < 0) {
            perror ("recvmsg");
            exit(1);
        }
        cmsg = CMSG_FIRSTHDR(&msg);
        if (cmsg && cmsg->cmsg_len == CMSG_LEN(sizeof(int))) {
            if (cmsg->cmsg_level != SOL_SOCKET) {
                fprintf (stderr, "invalid cmsg_level %d\n",
                     cmsg->cmsg_level);
                exit(1);
            }
            if (cmsg->cmsg_type != SCM_RIGHTS) {
                fprintf (stderr, "invalid cmsg_type %d\n",
                     cmsg->cmsg_type);
                exit(1);
            }

            *fd = *((int *) CMSG_DATA(cmsg));
            printf ("received fd %d\n", *fd);
        } else
            *fd = -1;
    } else {
        size = read (sock, buf, bufsize);
        if (size < 0) {
            perror("read");
            exit(1);
        }
    }
    return size;
}

//==============================================================================
//
//==============================================================================
void child(int sock) {
//    int fd;
//    char    buf[16];
//    ssize_t size;

//    sleep(1);
//    for (;;) {
//        size = sock_fd_read(sock, buf, sizeof(buf), &fd);
//        if (size <= 0)
//            break;
//        printf ("read %d\n", size);
//        if (fd != -1) {
//            write(fd, "hello, world\n", 13);
//            close(fd);
//        }
//    }
    sleep(1);
    while(1) {
        char buf[128];
        int fd;
        ssize_t size = sock_fd_read(sock, buf, sizeof(buf), &fd);
        if (size < 0) {
            break;
        } else {
            printf("Incoming message: \"%s\"\r\n", buf);
            if (fd != -1) {
                const char sockbuf[] = "Yeah!";
                if (send(fd, sockbuf, strlen(sockbuf), 0) < 0) {
                    perror("send");
                    break;
                }
                if (shutdown(fd, SHUT_RDWR) < 0) {
                    perror("shutdown");
                    break;
                }
                if (close(fd) < 0) {
                    perror("close");
                    break;
                }
            }
        }
    }

}

//==============================================================================
//
//==============================================================================
int parent(int sock)
{

    int enable = 1;
    int MasterSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (MasterSocket < 0) {
        perror("Can\'t create master socket!");
        return -1;
    }
    if (setsockopt(MasterSocket, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0) {
        perror("setsockopt");
        return -1;
    }
    sockaddr_in server_addr;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(DEFAULT_LISTENING_PORT);

    if (bind(MasterSocket, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        return -1;
    }

    if (listen(MasterSocket, SOMAXCONN) < 0) {
        perror("listen");
        return -1;
    }

    while(1) {
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int SlaveSocket = accept(MasterSocket, (sockaddr*)(&client_addr), &client_addr_len);
        if (SlaveSocket < 0) {
            perror("accept");
            return -1;
        }

        char client_addr_str[INET_ADDRSTRLEN] = {0};
        inet_ntop(AF_INET, &client_addr.sin_addr, client_addr_str, INET_ADDRSTRLEN);

        char client_desc_str[128];
        sprintf(client_desc_str, "addr: %s port: %d\n", client_addr_str, ntohs(client_addr.sin_port));

        ssize_t size = sock_fd_write(sock, client_desc_str, strlen(client_desc_str), SlaveSocket);
        if (size <= 0) {
            printf("sock_fd_write error!");

        }

        printf("Wrote %d bytes\r\n", size);

    }

    return 0;
//    fd = 1;
//    size = sock_fd_write(sock, "1", 1, 1);
//    printf ("wrote %d\n", size);
}

//==============================================================================
//
//==============================================================================
int main(int argc, char **argv)
{
    int sv[2];
    int pid;

    if (socketpair(AF_LOCAL, SOCK_STREAM, 0, sv) < 0) {
        perror("socketpair");
        exit(1);
    }
    switch ((pid = fork())) {
    case 0: // child
        close(sv[0]);
        child(sv[1]);
        break;
    case -1: // error
        perror("fork");
        exit(1);
    default: // parent
        close(sv[1]);
        parent(sv[0]);
        break;
    }
    return 0;
}
