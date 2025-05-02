/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_update_prompt
*/

#include <readline/buffer.h>


/*
** Updates the internal data buffer's prompt
** to the specified prompt.
*/
void rl_buffer_update_prompt(const char *prompt)
{
    string_buffer_t *buffer = rl_buffer_get();

    buffer->prompt = prompt;
}
