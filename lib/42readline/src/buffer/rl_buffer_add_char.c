/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_string_add_char
*/

#include <readline/buffer.h>
#include <stdlib.h>
#include <string.h>
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
static void grow_buffer(string_buffer_t *buffer)
{
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

/*
** Adds a char to the string buffer,
** increasing its size when needed.
*/
void rl_buffer_add_char(char c)
{
    string_buffer_t *buffer = rl_buffer_get();

    if (buffer->count + 1 >= buffer->capacity)
        grow_buffer(buffer);
    for (size_t i = buffer->count; i > buffer->arrow_index; i--)
        buffer->data[i] = buffer->data[i - 1];
    buffer->data[buffer->arrow_index] = c;
    buffer->arrow_index++;
    buffer->count++;
    buffer->data[buffer->count] = '\0';
}
