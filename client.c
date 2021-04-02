#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include <pthread.h>
#define IP "10.0.0.71"
#define PORT 6667

int init_csock(struct sockaddr_in *addr);
void conn_client(int cfd, struct sockaddr_in addr);
void *incoming_msg(void *cfd);
int input_val(char *input);

int main(void) {
    int clientfd;
    bool alive;
    struct sockaddr_in addr;
    char buf[1024] = {0};
    pthread_t thread;

    clientfd = init_csock(&addr);
    conn_client(clientfd, addr);
    pthread_create(&thread, 0, incoming_msg, &clientfd);

    alive = 1;
    while (alive) {
        printf(">> ");
        while(!input_val(fgets(buf, 1024, stdin))) {
            while (getchar() != '\n');
            printf("Character limit of 1024\n");
        }

        if (strcmp(buf, "/quit") == 0) 
            alive = 0;
        else if (send(clientfd, buf, strlen(buf), 0) < 0) {
            printf("Error sending message\n");
        } 
        memset(buf, 0, 1024);
    }

    close(clientfd);
    return 0;
}

/* Creates a socket used for client to connect to server */
int init_csock(struct sockaddr_in *addr) {
    int cfd;

    if ((cfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Error creating socket");
        exit(0);
    }

    addr->sin_family = AF_INET;
    addr->sin_port = htons(PORT);
    return cfd;
}

/* Client sends request to connect to server */
void conn_client(int cfd, struct sockaddr_in addr) {
    if (inet_pton(AF_INET, IP, &addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(0);
    }

    if (connect(cfd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        perror("Failed to connect");
        exit(0);
    }
}

/* Handles incoming messages from server */
void *incoming_msg(void *cfd){
    char msg[1024];
    bool alive = 1;
    
    while (alive) {
        alive = read(*(int*)cfd, msg, 1024);
        if (alive) {
            printf("%s\n", msg);
        }
        memset(msg, 0, 1024);
    }

    return NULL;
}

/* General user input validation meant to be used with fgets */
int input_val(char *input) {
    char *val;
    
    if ((val = strchr(input, '\n')) != NULL) {
        *val = '\0';        // null terminates string at newline
        return 1;
    }
    else
        return 0;
}
