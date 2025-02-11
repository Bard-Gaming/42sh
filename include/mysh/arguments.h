/*
** EPITECH PROJECT, 2025
** Project - Minishell 1
** File description:
** Description
*/

#ifndef SH_ARGUMENTS_H
    #define SH_ARGUMENTS_H
    #include <stdlib.h>
    #define SH_AB_INITIAL_CAPACITY 4
    #define SH_AB_GROWTH_FACTOR 1.5f


typedef struct {
    char **data;
    size_t count;
    size_t capacity;
} argument_buffer_t;


argument_buffer_t *argument_buffer_create(void);
void argument_buffer_delete(argument_buffer_t *buffer);
void argument_buffer_append(argument_buffer_t *buffer, const char *arg);
void argument_buffer_appendn(argument_buffer_t *buffer,
    const char *arg, size_t end);
argument_buffer_t *argument_buffer_from_line(const char *line);


#endif
