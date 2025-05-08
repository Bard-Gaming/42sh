/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Header file for readline's
** internal string buffer
*/

#ifndef LIB_READLINE_BUFFER_H
    #define LIB_READLINE_BUFFER_H
    #include <readline.h>
    #include <stddef.h>

    #define INITIAL_BUFFER_SIZE (1 << 7)
    #define CLEAR_LINE "\33[2K\r"
    #define INPUT_CURSOR "\033[5 q"
    #define AUTOCOMPLETE_LONG_CUTOFF 2

    #define UNUSED __attribute__((unused))


typedef struct {
    // Data:
    char *data;
    size_t count;
    size_t capacity;

    // TTY:
    const char *prompt;  // unowned (don't free)
    size_t arrow_index;
    size_t tabulation_count;

    // Configuration:
    autocomplete_fnc_t autocomplete;
    long_autocomplete_fnc_t autocomplete_long;

} string_buffer_t;


// Global getter:
string_buffer_t *rl_buffer_get(void);

// Control functions:
void rl_buffer_add_char(char c);
void rl_buffer_replace_char(char c, size_t index);
void rl_buffer_rm_char(void);
void rl_buffer_empty(void);

// Utils:
void rl_buffer_update_prompt(const char *prompt);
bool rl_buffer_is_tty_end(char input);
char *rl_buffer_get_data(void);
void rl_buffer_print(int fd);
void rl_buffer_autocomplete(void);
void rl_buffer_autocomplete_long(void);


#endif
