/*
 * Sample showing how to do SSH2 connect.
 *
 * The sample code has default values for host name, user name, password
 * and path to copy, but you can specify them on the command line like:
 *
 * "ssh2 host user password [-p|-i|-k]"
 */

#include "ssh2.h"
#include "libssh2_config.h"
#include <libssh2.h>
#include <libssh2_sftp.h>
#include <process.h>

#ifdef HAVE_WINDOWS_H
# include <windows.h>
#endif
#ifdef HAVE_WINSOCK2_H
# include <winsock2.h>
#endif
#ifdef HAVE_SYS_SOCKET_H
# include <sys/socket.h>
#endif
#ifdef HAVE_NETINET_IN_H
# include <netinet/in.h>
#endif
# ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
# ifdef HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif

#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>


const char *keyfile1="~/.ssh/id_rsa.pub";
const char *keyfile2="~/.ssh/id_rsa";

static void kbd_callback(const char *name, int name_len,
                         const char *instruction, int instruction_len,
                         int num_prompts,
                         const LIBSSH2_USERAUTH_KBDINT_PROMPT *prompts,
                         LIBSSH2_USERAUTH_KBDINT_RESPONSE *responses,
                         void **abstract)
{
    (void)name;
    (void)name_len;
    (void)instruction;
    (void)instruction_len;
    if (num_prompts == 1)
    {
        responses[0].text = strdup("password");
        responses[0].length = strlen("password");
    }
    (void)prompts;
    (void)abstract;
}

/**
 *\fn        void ssh_recv_data(my_ssh_param *param, const char *data, int len)
 *\brief     ssh接收数据
 *\param[in] my_ssh_param * param ssh参数数据
 *\param[in] const char * data 接收到的数据
 *\param[in] int len 接收到的数据长
 *\return    void 0成功,其它失败
 */
static int ssh_recv_data(my_ssh_param *param, const char *data, int len)
{
    if (NULL == param->recv_cb) return -1;

    return param->recv_cb(param->param, data, len);
}

/**
 *\fn        void recv_thread_func(void *param)
 *\brief     ssh接收数据线程
 *\param[in] void * param p_my_ssh_param
 *\return    void 0成功,其它失败
 */
void recv_thread_func(void *param)
{
    int rc = 1;
    char buffer[0x4000] = "";
    p_my_ssh_param ssh_param = (p_my_ssh_param)param;

    while (rc > 0 && 0 == ssh_param->exit)
    {
        rc = libssh2_channel_read(ssh_param->channel, buffer, sizeof(buffer)-1);

        if (rc <= 0)
        {
            ssh_param->exit = 1; // exit process
            fprintf(stderr,"libssh2_channel_read Error\n");
            break;
        }
        else
        {
            buffer[rc] = 0;
            ssh_param->recv_cb(ssh_param->param, buffer, rc);
        }
    }

    strcpy(buffer, "recv_thread_func exit\r\n");

    ssh_recv_data(ssh_param, buffer, strlen(buffer));
}

/**
 *\fn        int ssh_send_data(my_ssh_param *param, const char *data, int len)
 *\brief     ssh发送数据
 *\param[in] my_ssh_param * param ssh参数数据
 *\param[in] const char * data 要发送的数据
 *\param[in] int len 要发送的数据长
 *\return    int 0成功,其它失败
 */
int ssh_send_data(my_ssh_param *param, const char *data, int len)
{
    return libssh2_channel_write(param->channel, data, len);
}

/**
 *\fn        int run_ssh(p_my_ssh_param param)
 *\brief     ssh主线函数
 *\param[in] p_my_ssh_param param ssh参数数据
 *\return    int 0成功,其它失败
 */
int run_ssh(p_my_ssh_param param)
{
    int i = 0;
    int rc = 0;
    int sock = 0;
    int auth_pw = 0;
    char info[512] = "";
    const char *fingerprint = NULL;
    const char *userauthlist = NULL;
    LIBSSH2_SESSION *session = NULL;
    LIBSSH2_CHANNEL *channel = NULL;
    struct hostent *add_info = NULL;
    struct sockaddr_in srv_addr = {0};

#ifdef WIN32
    WSADATA wsadata;
    WSAStartup(MAKEWORD(2,0), &wsadata);
#endif
    
    if (NULL == param) return -1;

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
        sprintf(info, "failed to connect %s:%d!\r\n", param->server_addr, param->server_port);
        ssh_recv_data(param, info, strlen(info));
        return -1;
    }

    if (rc != libssh2_init(0))
    {
        sprintf(info, "libssh2 initialization failed (%d)\r\n", rc);
        ssh_recv_data(param, info, strlen(info));
        return 1;
    }

    /* Create a session instance and start it up. This will trade welcome
     * banners, exchange keys, and setup crypto, compression, and MAC layers
     */
    session = libssh2_session_init();

    if (NULL == session)
    {
        sprintf(info, "libssh2 create session failed\r\n");
        ssh_recv_data(param, info, strlen(info));
        return -1;
    }

    if (libssh2_session_handshake(session, sock))
    {
        sprintf(info, "Failure establishing SSH session\r\n");
        ssh_recv_data(param, info, strlen(info));
        return -1;
    }

    /* At this point we havn't authenticated. The first thing to do is check
     * the hostkey's fingerprint against our known hosts Your app may have it
     * hard coded, may go to a file, may present it to the user, that's your
     * call
     */
    fingerprint = libssh2_hostkey_hash(session, LIBSSH2_HOSTKEY_HASH_SHA1);
    sprintf(info, "Fingerprint: ");
    for(i = 0; i < 20; i++)
    {
        char temp[16] = "";
        sprintf(temp, "%02X ", (unsigned char)fingerprint[i]);
        strcat(info, temp);
    }
    strcat(info, "\r\n");
    ssh_recv_data(param, info, strlen(info));

    /* check what authentication methods are available */
    userauthlist = libssh2_userauth_list(session, param->username, strlen(param->username));

    sprintf(info, "Authentication methods: %s\r\n", userauthlist);
    ssh_recv_data(param, info, strlen(info));

    if (strstr(userauthlist, "password") != NULL)
    {
        auth_pw |= 1;
    }
    if (strstr(userauthlist, "keyboard-interactive") != NULL)
    {
        auth_pw |= 2;
    }
    if (strstr(userauthlist, "publickey") != NULL)
    {
        auth_pw |= 4;
    }

    if (auth_pw & 1)
    {
        /* We could authenticate via password */
        if (libssh2_userauth_password(session, param->username, param->password))
        {
            sprintf(info, "\tAuthentication by password failed!\r\n");
            ssh_recv_data(param, info, strlen(info));
            goto shutdown;
        }
        else
        {
            sprintf(info, "\tAuthentication by password succeeded.\r\n");
            ssh_recv_data(param, info, strlen(info));
        }
    }
    else if (auth_pw & 2)
    {
        /* Or via keyboard-interactive */
        if (libssh2_userauth_keyboard_interactive(session, param->username, &kbd_callback))
        {
            sprintf(info, "\tAuthentication by keyboard-interactive failed!\r\n");
            ssh_recv_data(param, info, strlen(info));
            goto shutdown;
        }
        else
        {
            sprintf(info, "\tAuthentication by keyboard-interactive succeeded.\r\n");
            ssh_recv_data(param, info, strlen(info));
        }
    }
    else if (auth_pw & 4)
    {
        /* Or by public key */
        if (libssh2_userauth_publickey_fromfile(session, param->username, keyfile1, keyfile2, param->password))
        {
            sprintf(info, "\tAuthentication by public key failed!\r\n");
            ssh_recv_data(param, info, strlen(info));
            goto shutdown;
        }
        else
        {
            sprintf(info, "\tAuthentication by public key succeeded.\r\n");
            ssh_recv_data(param, info, strlen(info));
        }
    }
    else
    {
        sprintf(info, "No supported authentication methods found!\r\n");
        ssh_recv_data(param, info, strlen(info));
        goto shutdown;
    }

    /* Request a shell */
    channel = libssh2_channel_open_session(session);

    if (NULL == channel)
    {
        sprintf(info, "Unable to open a session\r\n");
        ssh_recv_data(param, info, strlen(info));
        goto shutdown;
    }

    /* Some environment variables may be set,
     * It's up to the server which ones it'll allow though
     */
    libssh2_channel_setenv(channel, "FOO", "bar");

    /* Request a terminal with 'vanilla' terminal emulation
     * See /etc/termcap for more options
     */
    if (libssh2_channel_request_pty(channel, "ansi"))//vanilla
    {
        sprintf(info, "Failed requesting pty\r\n");
        ssh_recv_data(param, info, strlen(info));
        goto shutdown;
    }

    /* Open a SHELL on that pty */
    if (libssh2_channel_shell(channel))
    {
        sprintf(info, "Unable to request shell on allocated pty\r\n");
        ssh_recv_data(param, info, strlen(info));
        goto shutdown;
    }

    param->exit = 0;
    param->session = session;
    param->channel = channel;

    /*run recv message thread*/
    if (0 == _beginthread(recv_thread_func, 0, param))
    {
        sprintf(info, "_beginthread recv_thread_func fail\r\n");
        ssh_recv_data(param, info, strlen(info));
        goto shutdown;
    }

    /* At this point the shell can be interacted with using
     * libssh2_channel_read()
     * libssh2_channel_read_stderr()
     * libssh2_channel_write()
     * libssh2_channel_write_stderr()
     *
     * Blocking mode may be (en|dis)abled with: libssh2_channel_set_blocking()
     * If the server send EOF, libssh2_channel_eof() will return non-0
     * To send EOF to the server use: libssh2_channel_send_eof()
     * A channel can be closed with: libssh2_channel_close()
     * A channel can be freed with: libssh2_channel_free()
     */

    while (!param->exit) Sleep(100);

    if (channel)
    {
        libssh2_channel_free(channel);
        channel = NULL;
    }

    /* Other channel types are supported via:
     * libssh2_scp_send()
     * libssh2_scp_recv()
     * libssh2_channel_direct_tcpip()
     */

shutdown:

    libssh2_session_disconnect(session, "Normal Shutdown, Thank you for playing");
    libssh2_session_free(session);

#ifdef WIN32
    closesocket(sock);
#else
    close(sock);
#endif

    sprintf(info, "ssh:%s@%s:%d all done\r\n", param->username, param->server_addr, param->server_port);
    ssh_recv_data(param, info, strlen(info));

    libssh2_exit();

    param->exit = 1;
    param->session = NULL;
    param->channel = NULL;

    return 0;
}

/**
 *\fn        void ssh_thread_func(void *param)
 *\brief     ssh主线程
 *\param[in] void * param p_my_ssh_param
 *\return    void 0成功,其它失败
 */
void ssh_thread_func(void *param)
{
    const char *info = "ssh_thread_func exit\r\n\r\n\r\n\r\n\r\n";

    p_my_ssh_param ssh_param = (p_my_ssh_param)param;

    run_ssh(ssh_param);

    ssh_recv_data(ssh_param, info, strlen(info));
}

/**
 *\fn           int ssh_set_size(my_ssh_param *param, int width, int height)
 *\brief        设置屏幕宽高
 *\param[in]    my_ssh_param * param ssh参数数据
 *\param[in]    int width 屏幕宽
 *\param[in]    int height 屏幕高
 *\return       int 0成功,其它失败
 */
int ssh_set_size(my_ssh_param *param, int width, int height)
{
    if (NULL == param || width <= 0 || height <= 0) return -1;

    return libssh2_channel_request_pty_size(param->channel, width, height);
}
