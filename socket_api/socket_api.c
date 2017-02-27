/***********************************************************
**  File : Socket_API.C
**	Description : ���ڴ���TCP��API�ӿ�
**	Bug Report : huang_anming@126.com
**	Welcome to Qin Chi World !
***********************************************************/

/** ϵͳͷ�ļ� **/
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
/** �Զ���ͷ�ļ� **/
#include "socket_api.h"

typedef enum SOCKET_SATUS{
    ST_SUCCESS,
	ST_FAILED_BY_PORT,
	ST_FAILED_BY_ADDR,
}API_ST;


/***************************�ͻ���***************************/
/**
** �ͻ��� ���������ͻ��ˣ��ͻ���ʹ��������й���
**/
#define SOCKET_INIT(name) do {	\
    name = (struct SOCKET_ST *)malloc(sizeof(struct SOCKET_ST));	\
    name->fd = -1;	\
    name->port = -1;		\
    memset(name->ip_addr, 0, IP_ADDRESS_MAX_LEN);						\
}while(0);
/*
* ����һ���ͻ��˶����������ڹ���
*/
struct list_head *g_client_list;

int client_list_init(void)
{
	// ���ͻ��˽ṹ�Ƿ����
	if (NULL == g_tcp_client)
	{
		// ���ݽṹ��ʼ��
        SOCKET_TCP_INIT(g_tcp_client);
		// ��ʼ������ͷ
		LIST_HEAD_INIT(g_tcp_client->list);
	}
	// ���ӵ��ṹ��
	return 0;
}

int client_list_deinit(void)
{
	// ���ͻ��˽ṹ�Ƿ����
	if (NULL == g_tcp_client)
	{
		// ��ʼ������ͷ
		LIST_HEAD_INIT(g_tcp_client->list);
	}
}

/*
* �ͻ������ӹر�
* client �ͻ�����
* �����Ƿ�رտͻ��� 0-��ʾ�ɹ�
*/
int socket_disconnect(struct SOCKET_ST *client)
{
	return close(client->fd);
}

/*
* �ͻ������ӿ���
* client ���ӵķ������������
* ���� �Ƿ�ɹ����ӵ���������0-�ɹ�
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
* ��������
* client �ͻ�����Ϣ
* buf ���͵�����
* buf_len ���͵����ݳ���
* ���� ���͵����ݸ�����-1��ʾ����ʧ��
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
* ��������
* client �ͻ�����Ϣ
* buf �������ݿռ�
* buf_len �ܹ����յ����ݳ���
* ���� ���յ������ݸ����� -1��ʾ����ʧ��
*/
int socket_recv(struct SOCKET_TCP_ST *client, char *buf, int buf_len)
{
	if (client->fd < 0)
	{
		return -1;
	}
	return recv(client->fd, buf, buf_len, 0);
}



/***************************�����***************************/
/**
** ����� ����˽��ն��ͨ������ʹ��������й���
**/

#if 0
#define MYPORT  8887
#define BUFFER_SIZE 1024

int main()
{
    ///����sockfd
    int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

    ///����sockaddr_in
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(MYPORT);  ///�������˿�
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");  ///������ip

    ///���ӷ��������ɹ�����0�����󷵻�-1
    if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect");
        exit(1);
    }

    char sendbuf[BUFFER_SIZE];
    char recvbuf[BUFFER_SIZE];
    while (fgets(sendbuf, sizeof(sendbuf), stdin) != NULL)
    {
        send(sock_cli, sendbuf, strlen(sendbuf),0); ///����
        if(strcmp(sendbuf,"exit\n")==0)
            break;
        recv(sock_cli, recvbuf, sizeof(recvbuf),0); ///����
        fputs(recvbuf, stdout);

        memset(sendbuf, 0, sizeof(sendbuf));
        memset(recvbuf, 0, sizeof(recvbuf));
    }

    close(sock_cli);
    return 0;
}
#endif


