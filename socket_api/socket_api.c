/***********************************************************
**  File : Socket_API.C
**	Description : 用于创建TCP的API接口
**	Bug Report : huang_anming@126.com
**	Welcome to Qin Chi World !
***********************************************************/

/** 系统头文件 **/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include <fcntl.h>
#include <sys/shm.h>
/** 自定义头文件 **/
#include "socket_api.h"

typedef enum SOCKET_SATUS{
    ST_SUCCESS,
	ST_FAILED_BY_PORT,
	ST_FAILED_BY_ADDR,
}API_ST;


/***************************客户端***************************/
/**
** 客户端 创建多对象客户端，客户端使用链表进行管理
**/
#define SOCKET_INIT(name) do {	\
    name = (struct SOCKET_ST *)malloc(sizeof(struct SOCKET_ST));	\
    name->fd = -1;	\
    name->port = -1;		\
    memset(name->ip_addr, 0, IP_ADDRESS_MAX_LEN);						\
}while(0);
/*
* 创建一个客户端对象链表，用于管理
*/
struct list_head *g_client_list;

int client_list_init(void)
{
	// 检查客户端结构是否存在
	if (NULL == g_tcp_client)
	{
		// 数据结构初始化
        SOCKET_TCP_INIT(g_tcp_client);
		// 初始化链表头
		LIST_HEAD_INIT(g_tcp_client->list);
	}
	// 增加到结构中
	return 0;
}

int client_list_deinit(void)
{
	// 检查客户端结构是否存在
	if (NULL == g_tcp_client)
	{
		// 初始化链表头
		LIST_HEAD_INIT(g_tcp_client->list);
	}
}

/*
* 客户端链接关闭
* client 客户对象
* 返回是否关闭客户端 0-表示成功
*/
int socket_disconnect(struct SOCKET_ST *client)
{
	return close(client->fd);
}

/*
* 客户端链接开启
* client 链接的服务器对象参数
* 返回 是否成功链接到服务器，0-成功
*/
int socket_connect(struct SOCKET_ST *client)
{
	struct sockaddr_in addr;
	
	client->fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client->fd < 0)
	{
		perror("socket error:");
		return -1;
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons(client->port);
	if (inet_aton(client->ip_addr, &addr.sin_addr) == 0)
	//if (inet_aton(client->ip_addr, &addr.sin_addr.s_addr) == 0)
	{
		perror("ip address error:");
		close(client->fd);
		return -2;
	}
	if (connect(client->fd, (struct sockaddr*)&addr, 
									sizeof(struct sockaddr)) < 0)
	{
		perror("connect error:");
		close(client->fd);
		return -3;
	}
	return 0;
}

/*
* 发送数据
* client 客户端信息
* buf 发送的数据
* buf_len 发送的数据长度
* 返回 发送的数据个数，-1表示发送失败
*/
int socket_send(struct SOCKET_ST *client, char *buf, int buf_len)
{
	if (client->fd < 0)
	{
		return -1;
	}
	return send(client->fd, buf, buf_len, 0);
}

/*
* 接收数据
* client 客户端信息
* buf 接收数据空间
* buf_len 能够接收的数据长度
* 返回 接收到的数据个数， -1表示接收失败
*/
int socket_recv(struct SOCKET_TCP_ST *client, char *buf, int buf_len)
{
	if (client->fd < 0)
	{
		return -1;
	}
	return recv(client->fd, buf, buf_len, 0);
}



/***************************服务端***************************/
/**
** 服务端 服务端接收多个通信请求，使用链表进行管理
**/

#if 0
#define MYPORT  8887
#define BUFFER_SIZE 1024

int main()
{
    ///定义sockfd
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    ///定义sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///服务器端口
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///服务器ip

    ///连接服务器，成功返回0，错误返回-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        send(sock_cli, sendbuf, strlen(sendbuf),0); ///发送
        if(strcmp(sendbuf,"exit\n")==0)
            break;
        recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///接收
        fputs(recvbuf, stdout);

        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(sock_cli);
    return 0;
}
#endif


