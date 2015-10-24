#ifndef DIRECT_TCPIP
#define DIRECT_TCPIP
#include "ssh2.h"

typedef struct _tcpip_param
{
    int forwardsock;
    void *critical;

    unsigned int remote_destport;
    unsigned int local_srcport;

    my_ssh_param ssh_param;

}tcpip_param, *p_tcpip_param;

void port_map_thread_func(void* param);

#endif
