/***********************************************************
**  File : Socket_API.H
**	Description : 用于创建TCP的API接口
**	Bug Report : huang_anming@126.com
**	Welcome to Qin Chi World !
***********************************************************/

#ifndef SOCKET_API_H
#define SOCKET_API_H

#include "list.h"

#define IP_ADDRESS_MAX_LEN 16

struct SOCKET_ST{
	int fd;			// socket对象
    int port;				// 通信端口
	char ip_addr[IP_ADDRESS_MAX_LEN];	// 通信地址
	struct list_head list;	// 双向链表
};

/*
* 客户端链接开启
* client 链接的服务器对象参数
* 返回 是否成功链接到服务器，0-成功
*/
int socket_connect(struct SOCKET_ST *client);

/*
* 发送数据
* client 客户端信息
* buf 发送的数据
* buf_len 发送的数据长度
* 返回 发送的数据个数，-1表示发送失败
*/
int socket_send(struct SOCKET_ST *client, char *buf, int buf_len);

/*
* 接收数据
* client 客户端信息
* buf 接收数据空间
* buf_len 能够接收的数据长度
* 返回 接收到的数据个数， -1表示接收失败
*/
int socket_recv(struct SOCKET_TCP_ST *client, char *buf, int buf_len);

#endif	/* #ifndef SOCKET_TCP_API_H */
