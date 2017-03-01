/*************************************************************************
	> File Name: list_main_test.c
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Feb 2017 09:49:15 PM CST
 ************************************************************************/
#include <stdlib.h>
#include<stdio.h>

#include "list.h"

struct list_head *g_list;

struct TST_LIST{
    struct list_head list;
    int value;
};

int main()
{
    g_list = (struct list_head*)malloc(sizeof(struct list_head));
    struct TST_LIST list;
    struct list_head *p_list;
    struct TST_LIST *p_tst;

    INIT_LIST_HEAD(&list.list);
    //LIST_HEAD(list.list);
    list.value = 100;
    p_list = &list.list;

    p_tst = container_of(p_list, struct TST_LIST, list);
    printf("p_tst:value:%d\n", p_tst->value);

    INIT_LIST_HEAD(g_list);

    free(g_list);

    return 0;
}

