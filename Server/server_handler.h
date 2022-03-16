/*
 * Programmer:	Byron Gonzalez
 * Description:	Handles initialization and constant running of server
 * 		Receives client connections and messages
 */

#ifndef SERVER_HANDLER_H
#define SERVER_HANDLER_H

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "client_handler.h"

/*
 * Initializes server by sockaddr_in object that utalizes AF_INET
 *
 * param:	addr	sockaddr_in object used for server setup
 */
int init_server(struct sockaddr_in *addr);

/*
 * Begins broadcasting to allow clients to connect
 *
 * param:	sfd	Socket to host server on gets info from addr
 * 		addr	Provides server details
 */
void broadcast(int sfd, struct sockaddr_in addr);

/*
 * Accepts an incoming connection from client
 * 
 * param:	sfd	Listening server socket
 * 		addr	Provides server details
 */
int accept_conn(int sfd, struct sockaddr_in addr);

/*
 * Receives incoming client messages and echos them to all clients
 *
 * param:	cfd	Connected client
 */
void receive_msg(void *cfd);

#endif
