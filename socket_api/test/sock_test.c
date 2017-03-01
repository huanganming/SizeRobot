/*************************************************************************
	> File Name: sock_test.c
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Feb 2017 10:21:45 PM CST
 ************************************************************************/

#include<stdio.h>

#include "Socket_TCP_API.H"

int main()
{
    int flag = 0;
    char buf[100];

    struct SOCKET_TCP_ST st = {
        -1,
        8989,
        "192.168.0.152",
    };

    if (socket_tcp_connect(&st) == 0)
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }
    while(flag)
    {
        socket_tcp_recv(&st, buf, 100);
        printf("running %s\n", buf);
        sleep(1);
        socket_tcp_send(&st, "hello", 6);
    }

    return 0;
}

