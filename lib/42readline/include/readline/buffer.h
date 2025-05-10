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

    #define AUTOCOMPLETE_LONG_CUTOFF 2
    #define INITIAL_BUFFER_SIZE (1 << 7)


typedef struct {
    char *data;
    size_t count;
    size_t capacity;
} string_buffer_t;


// Global getter:
string_buffer_t *rl_buffer_get(void);

// Control functions:
void rl_buffer_add_char(char c);
void rl_buffer_insert_char(char c, size_t index);
void rl_buffer_replace_char(char c, size_t index);
void rl_buffer_rm_char(size_t index);
void rl_buffer_set(const char *src);
void rl_buffer_empty(void);
void rl_buffer_grow(void);

// Utils:
void rl_buffer_print(int fd);
bool rl_buffer_is_empty(void);
char *rl_buffer_get_data(void);


#endif
