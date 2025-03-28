/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_get
*/

#include <readline/buffer.h>


/*
** Gets a pointer to the library's
** internal buffer.
*/
string_buffer_t *rl_buffer_get(void)
{
    static string_buffer_t buffer = { 0 };

    return &buffer;
}
