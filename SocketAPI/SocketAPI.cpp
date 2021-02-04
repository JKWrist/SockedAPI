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

/****************************************************************
 * 函数
*****************************************************************/


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
 *          namelen 以字节为单位传递第二个结构体参数sockaddr的地址变量长度
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_connect(int s, const sockaddr *name, int namelen)
{
    int ret = -1;
    int error_len; //错误结果长度
    int error; //保存错误结果
    struct timeval timeout;
    fd_set fds;

    if(connect(s, name, namelen) == -1)
    {
        perror("Error");
        if(errno  == EINPROGRESS)//正在连接的情况
        {
            timeout.tv_sec = 5;
            timeout.tv_usec = 0;
            FD_ZERO(&fds);
            FD_SET(s, &fds);
            if(select(s + 1, NULL, &fds, NULL, &timeout) > 0)
            {
                if(FD_ISSET(s, &fds))
                {
                    error_len = 4;
                    error = -1;
                    getsockopt(s, SOL_SOCKET, SO_ERROR, &error, (socklen_t *)&error_len);
                    if(error == 0)
                    {
                        ret = 0;
                    }
                    else
                    {
                        ret = -1;
                    }
                }
                else
                {
                    ret = -1;
                }
            }
        }
        else
        {
            ret = -1;
        }
    }
    else
    {
        ret = 0;
    }

    return ret;
}

/****************************************************************
 * 功能描述:判断网络是否连接
 *  输入参数：无
 *  输出参数：无
 *  返回值：无
******************************************************************/
static int _write_send(int s, const void *data, int size, unsigned int flags)
{
    int ret = -1;
    int error = -1;
    int error_len = 4;
    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(s, &fds);
    switch(select(s + 1, NULL, &fds, NULL, timeout))
    {
    case -1:
        ret = -1; //select 出错
        break;

    case 0:
        ret = -1;
        break;

    default:
        if(FD_ISSET(s, &fds))
        {
            getsockopt(s, SOL_SOCKET, &error, (socklen_t *)&error_len);
        }
    }

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
