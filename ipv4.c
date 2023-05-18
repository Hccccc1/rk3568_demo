#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include <errno.h>

#define TCP_TEST

int tcp_create_and_connect(const char *ip_addr, int port)
{
    int ret;
    int fd;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("Socket create");
        return -1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    addr.sin_addr.s_addr = inet_addr(ip_addr);
    addr.sin_port = htons(port);
    addr.sin_family = AF_INET;
    socklen_t len = sizeof(addr);

    if (connect(fd, (struct sockaddr *)&addr, len) < 0)
    {
        perror("connect failed");
        goto out_close_socket;
    }

    return fd;

out_close_socket:
    close(fd);
    return -1;
}

int tcp_create_and_listen(uint16_t port)
{
    int ret;
    int fd;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
    {
        perror("Socket create");
        return -1;
    }

    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        goto out_close_socket;
    }

    if (listen(fd, 5) < 0)
    {
        perror("listen");
        goto out_close_socket;
    }

    return fd;

out_close_socket:
    close(fd);

    return -1;
}

int tcp_write(int socket_fd, const char *w_buf, uint16_t buf_len)
{
    return write(socket_fd, w_buf, buf_len);
}

int tcp_read(int socket_fd, char *r_buf, uint16_t buf_len)
{
    return read(socket_fd, r_buf, buf_len);
}

int udp_create_socket(uint16_t my_port)
{
    int fd;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
    {
        perror("udp socket");
        return -1;
    }

    struct sockaddr_in my_addr;
    my_addr.sin_addr.s_addr = INADDR_ANY;
    my_addr.sin_port = htons(my_port);
    my_addr.sin_family = AF_INET;

    if (bind(fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) < 0)
    {
        perror("udp bind");
        goto out_close_socket;
    }

    printf("%s %d\n", inet_ntoa(my_addr.sin_addr), ntohs(my_addr.sin_port));

    return fd;

out_close_socket:
    close(fd);

    return -1;
}

int udp_recv_from(int socket_fd, const char *ip_addr, uint16_t port, void *recv_buf, uint16_t buf_len)
{
    struct sockaddr_in from_addr;
    socklen_t len = sizeof(from_addr);

    from_addr.sin_addr.s_addr = inet_addr(ip_addr);
    from_addr.sin_port = htons(port);
    from_addr.sin_family = AF_INET;

    return recvfrom(socket_fd, recv_buf, buf_len, 0, (struct sockaddr *)&from_addr, &len);
}

int udp_send_to(int socket_fd, const char *ip_addr, uint16_t port, const void *send_buf, uint16_t buf_len)
{
    struct sockaddr_in to_addr;

    to_addr.sin_addr.s_addr = inet_addr(ip_addr);
    to_addr.sin_port = htons(port);
    to_addr.sin_family = AF_INET;

    return sendto(socket_fd, send_buf, buf_len, 0, (struct sockaddr *)&to_addr, sizeof(to_addr));
}

int main()
{
    int ret;
    int socket_fd;
    char buf[BUFSIZ] = {0};

    const char *str = "Hello world\n";

#ifdef TCP_TEST
/*client side*/
/*  
    if ((socket_fd = tcp_create_and_connect("172.16.21.83", 10001)) < 0)
        return -1;

    do
    {
        memset(buf, 0, sizeof(buf));

        if (tcp_read(socket_fd, buf, BUFSIZ) < 0)
            break;

        printf("read: %s\n", buf);

    } while (strncmp(buf, "quit", sizeof(char) * 4) != 0);

    close(socket_fd);
*/


/*Server side*/

    if ((socket_fd = tcp_create_and_listen(10001)) < 0)
        return -1;

    int afd;
    struct sockaddr_in c_addr;
    socklen_t c_len;

    if ((afd = accept(socket_fd, (struct sockaddr *)&c_addr, &c_len)) < 0)
        goto out_close_socket;

    printf("Clinet addr: %s, port %d\n", inet_ntoa(c_addr.sin_addr), ntohs(c_addr.sin_port));

    write(afd, str, strlen(str) + 1);

    do {
        memset(buf, 0, sizeof(buf));

        ret = read(afd, buf, BUFSIZ);

        printf("read %d -> %s\n", ret, buf);
    } while (strncmp(buf, "quit", strlen("quit")) != 0);

    close(afd);
    close(socket_fd);

#else

    if ((socket_fd = udp_create_socket(9999)) < 0)
        return -1;

    printf("send ret: %d\n", udp_send_to(socket_fd, "172.16.13.44", 10001, str, strlen(str) + 1));

    printf("recv ret: %d\n", udp_recv_from(socket_fd, "172.16.13.44", 10001, buf, BUFSIZ));

    printf("recv %s\n", buf);

    close(socket_fd);
#endif

    return 0;

out_close_socket:
    close(socket_fd);
    return errno;
}