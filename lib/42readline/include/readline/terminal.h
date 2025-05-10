/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Header file for terminal
** manipulation.
*/

#ifndef LIB_READLINE_TERMINAL_H
    #define LIB_READLINE_TERMINAL_H
    #include <sys/termios.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdio.h>

    // ----------- Terminal I/O ----------- :
    #define SEND_CODE_FD(fd, code) write(fd, code, strlen(code))
    #define SEND_CODE(term, code) SEND_CODE_FD(term->fd, code)

    // ----------- Erasing ----------- :
    #define CLEAR_LINE_FULL "\033[2K\r"
    #define CLEAR_LINE "\033[0K"

    // ----------- Cursor ----------- :
    // Style:
    #define CURSOR_LINE "\033[5 q"
    #define CURSOR_BLOCK "\033[1 q"

    // Position:
    #define CURSOR_LEFT "\033[D"
    #define CURSOR_RIGHT "\033[C"
    #define CURSOR_REQUEST_POS "\033[6n"


typedef struct {
    // OS TTY:
    struct termios settings;  // original settings to restore
    int fd;  // file descriptor for the terminal

    // State:
    unsigned short start_col;
    unsigned char tab_count;
    size_t history_index;
    size_t cursor_index;  // cursor index in buffer
} terminal_t;


typedef struct {
    int row;
    int col;
} cursor_pos_t;


// Terminal:
terminal_t *rl_terminal_get(void);

// Readline:
void rl_terminal_setup(int fd);
char *rl_terminal_readline(int fd);
void rl_terminal_cleanup(void);

void rl_terminal_add_char(char c);
void rl_terminal_handle_char(char c);
void rl_terminal_handle_control_char(char c);

// User control:
void rl_terminal_autocomplete(void);
void rl_terminal_autocomplete_long(void);

// Navigation:
void rl_terminal_next_word(void);
void rl_terminal_prev_word(void);

// Terminal Utility:
void rl_terminal_refresh(void);
void rl_terminal_clear(void);

// General Utility:
cursor_pos_t rl_terminal_get_cursor_pos(int fd);
void rl_terminal_set_cursor_pos(int fd, cursor_pos_t pos);
void rl_terminal_set_cursor_col(int fd, int col);


#endif
