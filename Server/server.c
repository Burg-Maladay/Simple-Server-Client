#include <stdio.h>
#include <stdlib.h>

#include "thpool.h"
#include "server_handler.h"

#define NUM_THREADS 10
#define PORT 6697

enum server_status {DEAD, ALIVE, FULL};

/* Global linked list holding connected clients */
clist *client_list;

int main(void) {
    int server_sock;
    int *cfd;
    struct sockaddr_in addr;
    enum server_status STATUS;
    threadpool pool;
    
    pool = thpool_init(NUM_THREADS);
    server_sock = init_server(&addr);
    broadcast(server_sock, addr);

    client_list = (clist*) malloc(sizeof(clist));
    STATUS = ALIVE;
    while (STATUS) {
        cfd = malloc(sizeof(int));
        *cfd = accept_conn(server_sock, addr);
        clist_insert(client_list, cfd);
        thpool_add_work(pool, *receive_msg, cfd);
    }
   
    clist_destroy(client_list);
    thpool_destroy(pool);
    close(server_sock);

    return 0;
}
