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

    #define MIN(a, b) ((a) < (b) ? (a) : (b))
    #define MAX(a, b) ((a) > (b) ? (a) : (b))
    #define CLAMP(lower, value, upper) MIN(MAX(lower, value), upper)


// Utils:
bool *rl_state_get(void);
char *rl_readline_file(int fd);

// Characters / Input:
bool rl_is_control_char(char c);
bool rl_is_word_char(char c);
char *rl_get_word(const char *input, size_t index);
char *rl_get_word_start(const char *input, size_t index);
char *rl_get_word_end(const char *input);
size_t rl_get_word_length(const char *input, size_t index);


#endif
