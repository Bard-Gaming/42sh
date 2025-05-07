/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Header file for internal
** library functions
*/

#ifndef LIB_READLINE_INTERNAL_H
    #define LIB_READLINE_INTERNAL_H
    #include <stdbool.h>
    #include <termios.h>
    #include <unistd.h>

    #define CHAR_DEL 127
    #define CHAR_EOT 4
    #define CONTROL_CHAR_MAX 31  // excludes DEL

    #define MIN(a, b) (a < b ? a : b)
    #define MAX(a, b) (a > b ? a : b)
    #define CLAMP(lower, value, upper) MIN(MAX(lower, value), upper)


bool *rl_state_get(void);

// Control characters:
bool rl_is_control_char(char c);
void rl_handle_control_char(char *input, ssize_t *read_len, int fd);

// Canonical mode:
void rl_disable_canonical_mode(int fd, struct termios *original);
void rl_restore_canonical_mode(struct termios *original);

// Readline functions:
char *rl_readline_tty(int fd, const char *prompt);
char *rl_readline_file(int fd);


#endif
