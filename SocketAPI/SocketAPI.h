//
//  Header.h
//  SockedAPI
//
//  Created by junze xu on 2020/6/21.
//  Copyright © 2020年 junze xu. All rights reserved.
//

#ifndef SOCKET_API_h
#define SOCKET_API_h
/****************************************************************
 * 文件包含
*****************************************************************/
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

/****************************************************************
 * 宏定义
*****************************************************************/
//socket 超时时间5秒
#define SOCKET_TIME_OUT (5)

#define ip_addr in_addr

#define _htonl(n) \
    (((n & 0xff) <<24) |\
    ((n & 0xff00) << 8) |\
    ((n & 0xff0000UL) >> 8) |\
    ((n & 0xff000000UL) >> 24))

#define ip4_addr1(ipaddr) ((_htonl((ipaddr)->s_addr) >> 24) & 0xff)
#define ip4_addr2(ipaddr) ((_htonl((ipaddr)->s_addr) >> 16) & 0xff)
#define ip4_addr3(ipaddr) ((_htonl((ipaddr)->s_addr) >> 8) & 0xff)
#define ip4_addr4(ipaddr) ((_htonl((ipaddr)->s_addr)) & 0xff)

inline void IP4_ADDR(struct ip_addr *addr, int ip1, int ip2, int ip3, int ip4)
{
    char buf[64];
    snprintf(buf, sizeof (buf), "%d, %d, %d, %d", ip1, ip2, ip3, ip4);
    printf("%s\n", buf);
    addr->s_addr = inet_addr(buf);
}

/****************************************************************
 * 杂项
*****************************************************************/
typedef int (*fn_isnetconnected)(void);
typedef int (*fn_socket)(int domain, int type, int protocol);
typedef int (*fn_connect)(int s, const sockaddr *name, int namelen);
typedef int (*fn_send)(int s, const void *data, int size, unsigned flags);
typedef int (*fn_recv)(int s, void *mem, int len, unsigned flags);
typedef int (*fn_setsockopt)(int s, int level, int optname, void *optaval, socklen_t optlen);
typedef int (*fn_getsockopt)(int s, int level, int optname, void *optval, socklen_t *optlen);
typedef int (*fn_closesocket)(int s);
typedef int (*fn_select)(int maxfdp1, fd_set *readset, fd_set *writeset, fd_set *exceptset, struct timeval *timeout);
typedef int (*fn_ioctl)(int s, long cmd, void *argp);


struct StructSocketAPI
{
    fn_isnetconnected isnetconnected;
    fn_socket socket;
    fn_connect connect;
    fn_send send;
    fn_recv recv;
    fn_setsockopt setsockopt;
    fn_getsockopt getsockopt;
    fn_closesocket closesocket;
    fn_select select;
    fn_ioctl ioctl;
};

/****************************************************************
 * 外部数据
*****************************************************************/
extern struct StructSocketAPI *sg_pSocketInterface;

/****************************************************************
 * 函数声明
*****************************************************************/
void SocketAbort(void);

#ifndef _DEFINE_SOCKETAPI
#define isnetconnected sg_pSocketInterface->isnetconnected
#define socket(a, b, c) sg_pSocketInterface->socket(a, b, c)
#define connect(a, b, c) sg_pSocketInterface->connect(a, b, c)
#define send(a, b, c, d) sg_pSocketInterface->send(a, b, c, d)
#define recv(a, b, c, d) sg_pSocketInterface->recv(a, b, c, d)
#define setsockopt(a, b, c, d, e) sg_pSocketInterface->setsockopt(a, b, c, d, e)
#define isnetconnected sg_pSocketInterface->isnetconnected
#define isnetconnected sg_pSocketInterface->isnetconnected

#endif

#endif /* SOCKET_API_h */
