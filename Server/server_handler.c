/*
 * Programmer:	Byron Gonzalez
 */

#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "server_handler.h"

#define PORT 6697

/* Creates socket along with socket options */
int init_server(struct sockaddr_in *addr) {
    int sfd;
    
    if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Failed creating socket");
        exit(0);
    }

    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int))) {
        perror("Failed setting socket options");
        exit(0);
    }

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(PORT);

    return sfd;
}

/* Binds server socket to PORT and listens for connections */
void broadcast(int sfd, struct sockaddr_in addr) {
if (bind(sfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Failed binding");
        exit(0);
    }
    
    if (listen(sfd, 3) < 0) {
        perror("Failed listening");
        exit(0);
    }

    time_t currTime;
    currTime = time(NULL);
    printf("Server started at %s", ctime(&currTime));
}


/* Accepts an incoming request to connect to server socket */
int accept_conn(int sfd, struct sockaddr_in addr) {
    int conn;
    
    if ((conn = accept(sfd, (struct sockaddr*)&addr,
                (socklen_t*) &(int){sizeof(addr)})) < 0) {
        perror("Failed accepting connection");
        exit(0);
    }
    printf("Connection established\n");

    return conn;
}

/* Server reads a message sent from a client */

extern clist *client_list;
void receive_msg(void *cfd) {
    int *c_socket = (int*)cfd;
    bool alive = 1;
    char msg[1024] = {0};
    char *success = "Successfully connected to server";

    send(*c_socket, success, strlen(success), 0);
    while (alive) {
        alive = read(*c_socket, msg, 1024);
        if (alive) {
            clist_send_msg(client_list, msg);
            printf("%s\n", msg);
        }
        memset(msg, 0, 1024);
    } 
   
    clist_remove(client_list, c_socket);
    close(*c_socket);
    free(c_socket);
    printf("Connection reset\n");
}
