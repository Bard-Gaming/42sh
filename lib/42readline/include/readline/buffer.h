/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Header file for readline's
** internal string buffer
*/

#ifndef LIB_READLINE_BUFFER_H
    #define LIB_READLINE_BUFFER_H

    #define INITIAL_BUFFER_SIZE (1 << 7)

    #include <stddef.h>
    #include <stdbool.h>


typedef struct {
    char *data;
    size_t count;
    size_t capacity;
} string_buffer_t;


string_buffer_t *rl_buffer_get(void);
char *rl_buffer_get_data(void);
bool rl_buffer_add_char(char c);
void rl_buffer_empty(void);


#endif
