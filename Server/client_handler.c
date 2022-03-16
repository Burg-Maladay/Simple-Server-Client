/*
 * Programmer:	Byron Gonzalez
 */

#include "client_handler.h"

struct client_node {
    c_node *next;
    int client_sock;
};

void clist_insert(clist *list, int *client_sock) {
    c_node *client = (c_node*) malloc(sizeof(c_node));
    client->next = NULL;
    client->client_sock = *client_sock;

    if (list->head == NULL) {
        list->head = client;
        list->tail = client;
        return;
    }

    list->tail->next = client;
    list->tail = client;
}

void clist_remove(clist *list, int *client_sock) {
    c_node *curr = list->head;
    c_node *prev = NULL;

    if (curr != NULL && curr->client_sock == *client_sock) {
        list->head = curr->next;
        free(curr);
        return;
    }
    
    while (curr != NULL && curr->client_sock != *client_sock) {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL)
        return;

    prev->next = curr->next;
    free(curr);
}

void clist_print(clist *list) {
    c_node *curr = list->head;
    
    while (curr != NULL) {
        printf("%d\n", curr->client_sock);
        curr = curr->next;
    }
}

void clist_send_msg(clist *list, char *buf) {
    c_node *curr = list->head;
    while (curr != NULL) {
        send(curr->client_sock, buf, strlen(buf), 0);
        curr = curr->next;
    }
}

void clist_destroy(clist *list) {
    c_node *curr = list->head;
    c_node *prev;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }
}
