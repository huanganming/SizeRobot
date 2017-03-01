/***********************************************************
**  File : bigiot_api.c
**	Description : www.bigiot.net
**	Bug Report : huang_anming@126.com
**	Welcome to Qin Chi World !
***********************************************************/

#include "bigiot_api.h"
#include "../socket_api.h"

#define DATA_MAX 512

#define IP_ADDRESS "121.42.180.30"
#define IP_PORT 8181

struct BIGIOT_ST{
	struct SOCKET_ST socket;
	char * id;
	char * data;
};

char command[][] = {
	"checkin",		// �豸��¼
	"update",		// ����ʵʱ����
	"login",		// �û����豸����֪ͨ����
	"logout",		// �û������豸����֪ͨ
	"say",			// �û����豸���豸���豸���û����û���ͨ
	"isOL",			// ��ѯ�豸�����û�����
	"status",		// ��ѯ��ǰ�豸״̬
	"alert",		// ���ͱ�����Ϣ
	"time",			// ��ѯ������ʱ��
	"checkout"		// ǿ��Ŀ��
};

enum CMD{
	CHECKIN,
	UPDATE,
	LOGIN,
	LOGOUT,
	SAY,
	ISOL,
	STATUS,
	ALERT,
	TIME,
	CHECKOUT
};

struct BIGIOT_ST *bigiot = NULL;

int bigiot_init(char *id)
{
	int id_len = strlen(id);
	
	bigiot = (struct BIGIOT_ST *)malloc(sizeof(struct BIGIOT_ST));
	
	bigiot->id = (char *)malloc(id_len);
	memcpy(bigiot->id, id, id_len);
	
	bigiot->data = (char *)malloc(DATA_MAX);
	
	bigiot->socket.fd = -1;
	bigiot->socket.port = IP_PORT;
	memcpy(bigiot->socket.ip_addr, IP_ADDRESS, strlen(IP_ADDRESS));
}

int bigiot_deinit()
{
	if (bigiot == NULL)
	{
		free(bigiot->data);
		free(bigiot->id);
		free(bigiot);
	}
}

int bigiot_checkin(char *key)
{
	int data_len = 0;
	// ��������
	memset(bigiot->data, 0, DATA_MAX);
	data_len = sprintf(bigiot->data, "{\"M\":\"%s\",\"ID\":\"%s\",\"K\":\"%s\"}\n", 
			command[CHECKIN], bigiot->id, key);
	socket_send(&bigiot->socket, bigiot->data, data_len);
	// ��������
	memset(bigiot->data, 0, DATA_MAX);
	socket_recv(&bigiot->socket, bigiot->data, DATA_MAX);
	
	return 0;
}

int bigiot_update(char *value)
{
	return 0;
}
