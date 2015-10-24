#include "direct_tcpip.h"
#include "libssh2_config.h"
#include <libssh2.h>
#include "ssh2.h"

#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#endif

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifdef HAVE_SYS_SELECT_H
#include <sys/select.h>
#endif

#ifndef INADDR_NONE
#define INADDR_NONE (in_addr_t)-1
#endif

/**
 *\fn        void printf_msg(my_ssh_param *param, const char *data, int len)
 *\brief     打印信息
 *\param[in] my_ssh_param * param ssh参数数据
 *\param[in] const char * data 接收到的数据
 *\param[in] int len 接收到的数据长
 *\return    void 0成功,其它失败
 */
static int printf_msg(my_ssh_param *param, const char *data, int len)
{
    if (NULL == param->recv_cb) return -1;

    return param->recv_cb(param->param, data, len);
}

void client_thread_func(void* param)
{
    int i = 0;
    int rc = 0;
    int once = 1;
    int once_remote = 1;
    char info[128] = "";
    p_my_ssh_param my_param = (p_my_ssh_param)param;
    int client_sock = (int)my_param->param;
    int local_srcport = (int)my_param->param1;
    int remote_destport = (int)my_param->param2;
    CRITICAL_SECTION *critical = (CRITICAL_SECTION*)my_param->param3;
    LIBSSH2_SESSION *session = (LIBSSH2_SESSION*)my_param->session;
    LIBSSH2_CHANNEL *channel = NULL;

    fd_set fds;
    struct timeval tv = {0};
    ssize_t len = 0, wr = 0;

    int buf_len = 1024*1024;
    char *buf = (char*)malloc(buf_len);

    sprintf(info, "Forwarding connection from 127.0.0.1:%d here to remote %s:%d\n",
        local_srcport, my_param->server_addr, remote_destport);
    printf_msg(my_param, info, strlen(info));

    for (i = 0; i < 100; i++)
    {
        channel = libssh2_channel_direct_tcpip_ex(session, "localhost",
            remote_destport, "127.0.0.1", local_srcport);

        if (NULL != channel)
        {
            break;
        }
        else
        {
            Sleep(100);
        }
    }

    if (!channel)
    {
        const char *info= "Could not open the direct-tcpip channel!\n";
        printf_msg(my_param, info, strlen(info));
        goto over;
    }

    while (once)
    {
        FD_ZERO(&fds);
        FD_SET(client_sock, &fds);
        tv.tv_sec = 0;
        tv.tv_usec = 100000;

        rc = select(client_sock + 1, &fds, NULL, NULL, &tv);
        if (-1 == rc)
        {
            perror("select");
            goto over;
        }

        if (rc && FD_ISSET(client_sock, &fds))
        {
            len = recv(client_sock, buf, buf_len, 0);

            if (len < 0)
            {
                perror("read");
                goto over;
            }
            else if (0 == len)
            {
                sprintf(info, "The client at 127.0.0.1:%d disconnected!\n", local_srcport);
                printf_msg(my_param, info, strlen(info));
                goto over;
            }

            wr = 0;

            do
            {
                EnterCriticalSection(critical);

                i = libssh2_channel_write(channel, buf, len);

                LeaveCriticalSection(critical);

                if (i < 0)
                {
                    sprintf(info, "libssh2_channel_write: %d\n", i);
                    printf_msg(my_param, info, strlen(info));
                    goto over;
                }

                wr += i;

            } while(i > 0 && wr < len);

            once_remote = 1;
        }

        while (once_remote)
        {
            EnterCriticalSection(critical);

            len = libssh2_channel_read(channel, buf, buf_len);

            LeaveCriticalSection(critical);

            if (LIBSSH2_ERROR_EAGAIN == len)
            {
                break;
            }
            else if (len < 0)
            {
                sprintf(info, "libssh2_channel_read: %d\n", (int)len);
                printf_msg(my_param, info, strlen(info));
                goto over;
            }

            wr = 0;

            while (wr < len)
            {
                i = send(client_sock, buf + wr, len - wr, 0);

                if (i <= 0)
                {
                    perror("write");
                    goto over;
                }

                wr += i;
            }

            if (libssh2_channel_eof(channel))
            {
                sprintf(info, "The server at %s:%d disconnected!\n", 
                    my_param->server_addr, remote_destport);

                printf_msg(my_param, info, strlen(info));

                goto over;
            }
        }
    }

over:

#ifdef WIN32
    closesocket(client_sock);
#else
    close(client_sock);
#endif

    if (channel)
    {
        libssh2_channel_free(channel);
    }

    free(buf);

    sprintf(info, "The client at 127.0.0.1:%d disconnected!\n", local_srcport);

    printf_msg(my_param, info, strlen(info));
}

int run_port_map(p_my_ssh_param param)
{
    int rc = 0;
    int sock = 0;
    int sockopt = 1;
    int listensock = -1;
    char info[512] = "";
    LIBSSH2_SESSION *session = NULL;
    struct hostent *add_info = NULL;
    struct sockaddr_in sin = {0};
    struct sockaddr_in srv_addr = {0};
    CRITICAL_SECTION critical;

#ifdef WIN32
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,0), &wsadata);
#endif

    if (NULL == param) return -1;

    InitializeCriticalSection(&critical);

    param->param3 = &critical;

    /* Ultra basic "connect to port 22 on localhost".  Your code is
     * responsible for creating the socket establishing the connection
     */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(param->server_port);
    srv_addr.sin_addr.s_addr = inet_addr(param->server_addr);

    add_info = gethostbyname(param->server_addr);

    if (NULL != add_info)
    {
        memcpy(&srv_addr.sin_addr, add_info->h_addr_list[0], add_info->h_length);
    }

    if (connect(sock, (struct sockaddr*)(&srv_addr), sizeof(struct sockaddr_in)) != 0)
    {
        sprintf(info, "failed to connect!\n");
        printf_msg(param, info, strlen(info));
        return -1;
    }

    if (rc != libssh2_init(0))
    {
        sprintf(info, "libssh2 initialization failed (%d)\n", rc);
        printf_msg(param, info, strlen(info));
        return 1;
    }

    /* Create a session instance and start it up. This will trade welcome
     * banners, exchange keys, and setup crypto, compression, and MAC layers
     */
    session = libssh2_session_init();

    if (NULL == session)
    {
        sprintf(info, "libssh2 create session failed\n");
        printf_msg(param, info, strlen(info));
        return -1;
    }

    if (libssh2_session_handshake(session, sock))
    {
        sprintf(info, "Failure establishing SSH session\n");
        printf_msg(param, info, strlen(info));
        return -1;
    }

    /* We could authenticate via password */
    if (libssh2_userauth_password(session, param->username, param->password))
    {
        sprintf(info, "Authentication by password failed!\n");
        printf_msg(param, info, strlen(info));
        goto shutdown;
    }

    param->exit = 0;
    param->channel = NULL;
    param->session = session;

    listensock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    sin.sin_family = AF_INET;
    sin.sin_port = htons((u_short)(int)param->param1);

    if (INADDR_NONE == (sin.sin_addr.s_addr = inet_addr("127.0.0.1")))
    {
        perror("inet_addr");
        goto shutdown;
    }

    setsockopt(listensock, SOL_SOCKET, SO_REUSEADDR, (const char*)&sockopt, sizeof(sockopt));

    if (-1 == bind(listensock, (struct sockaddr *)&sin, sizeof(struct sockaddr_in)))
    {
        perror("bind");
        sprintf(info, "Bind local socket %d failed!\n", param->param1);
        printf_msg(param, info, strlen(info));
        goto shutdown;
    }

    if (-1 == listen(listensock, 2))
    {
        perror("listen");
        goto shutdown;
    }

    sprintf(info, "Waiting for TCP connection on %s:%d...\n", inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
    printf_msg(param, info, strlen(info));

    /* Must use non-blocking IO hereafter due to the current libssh2 API */
    libssh2_session_set_blocking(session, 0);

    while (1 != param->exit)
    {
        int sinlen = sizeof(struct sockaddr_in);
        int client_socket = accept(listensock, (struct sockaddr *)&sin, &sinlen);

        if (-1 == client_socket)
        {
            sprintf(info, "port %d accept client faile\n", param->param1);
            printf_msg(param, info, strlen(info));
            goto shutdown;
        }
        param->param = (void*)client_socket;
        param->param1 = (void*)(u_long)ntohs(sin.sin_port);

        _beginthread(client_thread_func, 0, param);
    }

shutdown:
    libssh2_session_disconnect(session, "Normal Shutdown, Thank you for playing\n");
    libssh2_session_free(session);

#ifdef WIN32
    closesocket(listensock);
#else
    close(listensock);
#endif

    sprintf(info, "postmap:%s@%s:%d all done\n", param->username, param->server_addr, param->server_port);
    printf_msg(param, info, strlen(info));

    libssh2_exit();

    param->session = NULL;
    param->channel = NULL;
    param->exit = 1;

    free(param);

    DeleteCriticalSection(&critical);

    return 0;
}

void port_map_thread_func(void* param)
{
    p_my_ssh_param ssh_param = (p_my_ssh_param)param;

    run_port_map(ssh_param);
}

