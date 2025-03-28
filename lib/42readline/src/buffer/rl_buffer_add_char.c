/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_string_add_char
*/

#include <readline/buffer.h>
#include <stdlib.h>


static bool grow_buffer(string_buffer_t *buffer)
{
    size_t new_capacity = buffer->capacity == 0 ?
        INITIAL_BUFFER_SIZE : buffer->capacity * 2;
    char *new_buffer;

    if (new_capacity <= buffer->capacity)
        return false;
    new_buffer = malloc(new_capacity * sizeof(char));
    if (new_buffer == NULL)
        return false;
    for (size_t i = 0; i < buffer->count; i++)
        new_buffer[i] = buffer->data[i];
    free(buffer->data);
    buffer->data = new_buffer;
    buffer->capacity = new_capacity;
    return true;
}

/*
** Adds a char to the string buffer,
** increasing its size when needed.
*/
bool rl_buffer_add_char(char c)
{
    string_buffer_t *buffer = rl_buffer_get();

    if (buffer->count + 1 >= buffer->capacity)
        if (!grow_buffer(buffer))
            return false;
    buffer->data[buffer->count] = c;
    buffer->count++;
    buffer->data[buffer->count] = '\0';
    return true;
}
