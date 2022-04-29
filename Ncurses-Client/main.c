#include "interface.h"    // must be first include; view first line
#include "client.h"

#include <locale.h>

void interface(WINDOW *chatbox_win, WINDOW *input_win,
    const int client);

bool send_msg(const wchar_t *buffer, const int client);

int main() {
  setlocale(LC_ALL, "");  // allow wide characters
  
  int client;
  struct sockaddr_in addr;

  client = initialize_client(&addr);
  request_connection(client, addr);
  
  initscr();
  WINDOW *chatbox_win = newwin(LINES-3, COLS, 0, 0);
  WINDOW *input_win = newwin(0, COLS-3, LINES-1, 3);
  scrollok(chatbox_win, true);
  scrollok(input_win, true);

  mvprintw(LINES-1, 0, ">>");
  refresh();

  interface(chatbox_win, input_win, client);

  endwin();
  close(client);
  return 0;
}

void interface(WINDOW *chatbox_win, WINDOW *input_win,
    const int client) {
  wchar_t buffer[MSG_LENGTH];

  while (wcscmp(buffer, L"/quit") != 0) {
    get_input(input_win, buffer);
    wcscpy(buffer, trim_spaces(buffer));
    if(!send_msg(buffer, client))
      perror("Error occurred when attempting to send message to server");
    wrefresh(chatbox_win);
  }
}

bool send_msg(const wchar_t *buffer, const int client) {
  if (validate_msg(buffer)) {
    if (send(client, buffer, sizeof(wchar_t) * wcslen(buffer), 0) < 0) {
      return false;
    }
  }
  return true;
}
