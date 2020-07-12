
/****************************************************************
 *  Copyright © 2020年 junze xu. All rights reserved.
 *  All rights reserved.
 *
 *  文件名称: SockedAPI.cpp
 *  简要描述:
 *
 *  创建日期: Created by junze xu on 2020/6/21.
 *  作者: junze xu
 *  说明:
 *
 *  修改日期:
 *  作者:
 *  说明:
*****************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "SocketAPI.h"

/****************************************************************
 * 全局变量
*****************************************************************/
static int socket_abort = 0;
/****************************************************************
 * 函数
*****************************************************************/

/****************************************************************
 * 功能描述:取消socket传输
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
void SocketAbort(void)
{
    socket_abort = 1;
}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
int is_netconnected(void)
{
    return 1;
}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_isnetconnected(void)
{
    if(0 == is_netconnected())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/****************************************************************
 * 功能描述:创建非阻塞socket
 *  输入参数： domain 协议族
 *           type 数据传输类型
 *           protocol 计算机通信中使用的协议信息
 *  输出参数：成功-0， 失败-（-1）
 *  返回值：无
******************************************************************/
static int _write_socket(int domain, int type, int protocol)
{
    int ul = 4;
    int sockfd;
    sockfd = socket(domain, type, protocol);

    if(sockfd > 0)
    {
        ioctl(sockfd, FIONBIO, &ul);
    }
    return sockfd;
}

/****************************************************************
 * 功能描述:请求连接
 *  输入参数：s-文件描述符
 *          name-保存目标服务端地址信息
 *          namelen
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_connect(int s, const sockaddr *name, int namelen)
{

}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_send(int s, const void *data, int size, unsigned int flags)
{

}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_recv(int s, void *mem, int len, unsigned int flags)
{

}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_setsockopt(int s, int level, int optname, void *optval, socklen_t oplen)
{

}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_getsockopt(int s, int level, int optname, void *optval, socklen_t *oplen)
{

}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_closesocket(int s)
{
    return close(s);
}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_select(int maxfdp, fd_set *readset, fd_set *writeset, fd_set *exceptset, struct timeval *timeout)
{

}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_ioctl(int s, long cmd, void *argp)
{
    return ioctl(s, cmd, argp);
}


static struct StructSocketAPI sg_twriteSocket = {
    _write_isnetconnected,
    _write_socket,
    _write_connect,
    _write_send,
    _write_recv,
    _write_setsockopt,
    _write_getsockopt,
    _write_closesocket,
    _write_select,
    _write_ioctl
};
