/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Header file for readline's
** internal string buffer
*/

#ifndef LIB_READLINE_STRING_H
    #define LIB_READLINE_STRING_H

    #define INITIAL_BUFFER_SIZE (1 << 7)

    #include <stddef.h>
    #include <stdbool.h>


typedef struct {
    char *data;
    size_t count;
    size_t capacity;
} string_buffer_t;


bool rl_string_add_char(string_buffer_t *buffer, char c);
void rl_string_empty(string_buffer_t *buffer);


#endif
