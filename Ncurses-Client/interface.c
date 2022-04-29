#include "interface.h"

wchar_t *get_input(WINDOW *input_win, wchar_t *buffer) {
  // cast to get wide character formating when entering text
  wgetn_wstr(input_win, (wint_t*)buffer, MSG_LENGTH);
  werase(input_win);
  return buffer;
}
