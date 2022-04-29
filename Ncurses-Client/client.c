#include "client.h"

int initialize_client(struct sockaddr_in *addr) {
  int client;

  // Creates the socket
  if ((client = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Error creating socket");
    exit(0);
  }

  // Saves network settings
  addr->sin_family = AF_INET;
  addr->sin_port = htons(PORT);
  return client;
}

void request_connection(const int client, struct sockaddr_in addr) {
  if (inet_pton(AF_INET, IP, &addr.sin_addr) <= 0) {
    perror("Invalid address");
    close(client);
    exit(0);
  }

  if (connect(client, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
    perror("Failed to connect");
    close(client);
    exit(0);
  }
}

void *handle_incoming_msg(void *client, WINDOW *chatbox) {
  wchar_t buffer[1024];

  while (1) {
    read(*(int*)client, buffer, MSG_LENGTH);
    waddwstr(chatbox, buffer);
  }
  return NULL;
}

bool validate_msg(const wchar_t *buffer) {
  if (*buffer != 0 && buffer[0] != '/')
    return true;
  return false;
}

wchar_t *trim_spaces(wchar_t *buffer) {
  wchar_t *trimmed;

  while (isspace((unsigned char)*buffer))
    buffer++;
  
  if (*buffer == 0)
    return buffer;

  // set trimmed to memory value before NULL and go backward through memory
  trimmed = buffer + wcslen(buffer) - 1;
  while (trimmed > buffer && isspace((unsigned char)*trimmed))
    trimmed--;

  trimmed[1] = '\0';

  return buffer;
}
