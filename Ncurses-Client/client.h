#ifndef CLIENT_H
#define CLIENT_H

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include "interface.h"

#define IP "10.0.0.71"
#define PORT 6697

/*
 * Sets up the client socket using AF_INET
 * Param:
 * addr - used to create client socket
 * Return:
 * client socket
 */
int initialize_client(struct sockaddr_in *addr);

/*
 * Sends a connection request to the server
 * Param:
 * client - socket that will be used to connect to server
 * addr - saved socket settings
 */
void request_connection(const int client, struct sockaddr_in addr);

/*
 * Receives and prints an incoming message onto an ncurses window
 * Param:
 * client - socket connected to server
 * chatbox - ncurses window to print to
 */
void *handle_incoming_msg(void *client, WINDOW *chatbox);

/*
 * Ensures buffer is null terminated and isn't a client command
 * Param:
 * buffer - wchar_t array to be validated
 * Return:
 * True if no issues were found with buffer
 */
bool validate_msg(const wchar_t *buffer);

/*
 * Remove leading and trailing spaces from buffer
 * Param:
 * buffer - wchar_t array to have spaces trimmed
 * Return:
 * buffer without leading or trailing spaces
 */
wchar_t *trim_spaces(wchar_t *buffer);

#endif
