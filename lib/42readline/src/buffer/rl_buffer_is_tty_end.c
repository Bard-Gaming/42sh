/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_is_tty_end
*/

#include <readline/buffer.h>
#include <readline/internal.h>


/*
** Tells whether or not readline should
** end in a <user end> or not.
*/
bool rl_buffer_is_tty_end(char input)
{
    string_buffer_t *buffer = rl_buffer_get();

    return
        input == CHAR_EOT &&
        buffer->count == 0;
}
