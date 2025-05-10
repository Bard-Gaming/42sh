/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_grow
*/

#include <readline/buffer.h>
#include <stdlib.h>
#include <stdio.h>


/*
** Exits the program with the given
** error message.
*/
static void exit_error(const char *msg)
{
    printf("readline: error: %s\n", msg);
    exit(84);
}

/*
** Grows the buffer to be able to store
** more data.
*/
void rl_buffer_grow(void)
{
    string_buffer_t *buffer = rl_buffer_get();
    size_t new_capacity = buffer->capacity == 0 ?
        INITIAL_BUFFER_SIZE : buffer->capacity * 2;

    if (new_capacity <= buffer->capacity)
        exit_error("memory limit reached");
    buffer->data = reallocarray(
        buffer->data,
        new_capacity,
        sizeof(char)
    );
    if (buffer->data == NULL)
        exit_error("not enough memory available");
    buffer->capacity = new_capacity;
}
