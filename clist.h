#ifndef CLIST_H
#define CLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

struct client_node;
typedef struct client_node c_node;

struct client_list {
    c_node *head;
    c_node *tail;
};
typedef struct client_list clist;

void clist_insert(clist *list, int *client_sock);
void clist_remove(clist *list, int *client_sock);
void clist_print(clist *list);
void clist_send_msg(clist *list, char *buf);
void clist_destroy(clist *list);

#endif
