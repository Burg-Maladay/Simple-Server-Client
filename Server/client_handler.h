/*
 * Programmer:	Byron Gonzalez
 * Description:	Handles incoming client connection and disconnections requests
 * 		along with sending messages to all currently connected clients
 */

#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

struct client_node;
typedef struct client_node c_node;

/*
 * Linked list that will hold all clients for easy handling
 */
struct client_list {
    c_node *head;
    c_node *tail;
};
typedef struct client_list clist;


/*
 * Inserts a client node into a linked list.
 *
 * param	list		linked list holding all clients on server
 * 		client_sock	socket being used for client
 * 
 */
void clist_insert(clist *list, int *client_sock);


/*
 * Removes a client node from linked list.
 *
 * param	list		linked list holding all clients on server
 * 		client_sock	socket being used for client
 */
void clist_remove(clist *list, int *client_sock);


/*
 * Prints all currently connected clients
 *
 * param	list		linked list holding all clients on server
 *
 */
void clist_print(clist *list);

/*
 * Sends message to all currently connected clients
 *
 * param	list		linked list holding all clients on server
 * 		buf		contents of message
 */
void clist_send_msg(clist *list, char *buf);

/*
 * Removes all currently connected clients from server
 *
 * param	list		linked list holding all clinets on server
 */
void clist_destroy(clist *list);

#endif
