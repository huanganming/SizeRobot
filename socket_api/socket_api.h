/***********************************************************
**  File : Socket_API.H
**	Description : ���ڴ���TCP��API�ӿ�
**	Bug Report : huang_anming@126.com
**	Welcome to Qin Chi World !
***********************************************************/

#ifndef SOCKET_API_H
#define SOCKET_API_H

#include "list.h"

#define IP_ADDRESS_MAX_LEN 16

struct SOCKET_ST{
	int fd;			// socket����
    int port;				// ͨ�Ŷ˿�
	char ip_addr[IP_ADDRESS_MAX_LEN];	// ͨ�ŵ�ַ
	struct list_head list;	// ˫������
};

/*
* �ͻ������ӿ���
* client ���ӵķ������������
* ���� �Ƿ�ɹ����ӵ���������0-�ɹ�
*/
int socket_connect(struct SOCKET_ST *client);

/*
* ��������
* client �ͻ�����Ϣ
* buf ���͵�����
* buf_len ���͵����ݳ���
* ���� ���͵����ݸ�����-1��ʾ����ʧ��
*/
int socket_send(struct SOCKET_ST *client, char *buf, int buf_len);

/*
* ��������
* client �ͻ�����Ϣ
* buf �������ݿռ�
* buf_len �ܹ����յ����ݳ���
* ���� ���յ������ݸ����� -1��ʾ����ʧ��
*/
int socket_recv(struct SOCKET_TCP_ST *client, char *buf, int buf_len);

#endif	/* #ifndef SOCKET_TCP_API_H */
