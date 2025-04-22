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
* cut the string at the right index
*/
bool cut_buffer(void)
{
    string_buffer_t *buffer = rl_buffer_get();
    size_t new_capacity = buffer->capacity == 0 ?
        INITIAL_BUFFER_SIZE : buffer->capacity * 2;
    char *new_buffer;
    int index = 0;

    new_buffer = malloc(sizeof(char) * new_capacity);
    if (!new_buffer)
        return false;
    memset(new_buffer, '\0', new_capacity);
    for (size_t i = 0; i < buffer->count; i++) {
        if (index == buffer->arrow_index)
            continue;
        new_buffer[i] = buffer->data[index];
        index++;
    }
    free(buffer->data);
    buffer->data = new_buffer;
    buffer->capacity = new_capacity;
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
    buffer->arrow_index++;
    printf("char added at index: %i\n", buffer->arrow_index);
    return true;
}
