/*
** EPITECH PROJECT, 2025
** multishell
** File description:
** rl_prompt_autcomplete
*/

#include <readline.h>
#include <readline/buffer.h>

void rl_handle_autocompletion(void)
{
    string_buffer_t *buffer = rl_buffer_get();
    char *temp;

    temp = buffer->autocomplete(buffer->data);
}