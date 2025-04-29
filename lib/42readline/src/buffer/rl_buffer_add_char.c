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

    if (buffer->count + 1 >= buffer->capacity) {
        if (!grow_buffer(buffer))
            return false;
    }
    if (buffer->arrow_index < buffer->count) {
        for (size_t i = buffer->count; i > buffer->arrow_index; i--) {
            buffer->data[i] = buffer->data[i - 1];
        }
    }
    buffer->data[buffer->arrow_index] = c;
    buffer->count++;
    buffer->data[buffer->count] = '\0';
    buffer->arrow_index++;
    return true;
}

/*
* cut the string at the right index
*/
bool cut_buffer(void)
{
    string_buffer_t *buffer = rl_buffer_get();
    size_t new_capacity = buffer->capacity == 0 ?
        INITIAL_BUFFER_SIZE : buffer->capacity * 2;
    int index = buffer->arrow_index - 1;
    size_t len = strlen(buffer->data);
    char *new_buffer;

    if (buffer->arrow_index == 0 || buffer->count == 0)
        return false;
    new_buffer = malloc(sizeof(char) * new_capacity);
    if (!new_buffer)
        return false;
    memcpy(new_buffer, buffer->data, index);
    memcpy(new_buffer + index, buffer->data + index + 1, len - index);
    buffer->data = new_buffer;
    return true;
}
