/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_string_add_char
*/

#include <readline/string.h>
#include <stdlib.h>


bool grow_buffer(string_buffer_t *buffer)
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
    buffer->capacity = new_capacity;
    buffer->data = new_buffer;
    return true;
}

/*
** Adds a char to the string buffer,
** increasing its size when needed.
*/
bool rl_string_add_char(string_buffer_t *buffer, char c)
{
    if (buffer->count + 1 >= buffer->capacity)
        if (!grow_buffer(buffer))
            return false;
    buffer->data[buffer->count] = c;
    buffer->count++;
    buffer->data[buffer->count] = '\0';
    return true;
}
