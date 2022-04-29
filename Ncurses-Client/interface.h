/*
 * Allows ncurses to use wide characters
 * Must define this before any and all includes
 */
#define _XOPEN_SOURCE 700

#ifndef INTERFACE_H
#define INTERFACE_H

#include <ncurses.h>
#include <ctype.h>
#include <wchar.h>

#define MSG_LENGTH 256

wchar_t *get_input(WINDOW* input, wchar_t *buffer);

#endif
