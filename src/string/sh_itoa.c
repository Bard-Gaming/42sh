/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_itoa
*/

#include <42sh/string.h>


/*
** Recursively fills the given buffer
** with the provided (positive) integer.
*/
static void fill_buffer(char **buffer, int value)
{
    if (value == 0)
        return;
    fill_buffer(buffer, value / 10);
    **buffer = value % 10 + '0';
    (*buffer)++;
}

/*
** Fills the buffer with the
** representation of 0.
** This has to be treated separately,
** as 0 is the base case.
*/
static void zero_repr(char *buffer)
{
    buffer[0] = '0';
    buffer[1] = '\0';
}

/*
** Stores a string representation
** of the given integer value into
** the buffer, including NULL byte.
** The given buffer is assumed to
** be able to hold ITOA_MAX bytes
** of memory.
*/
void sh_itoa(char *buffer, int value)
{
    char **current = &buffer;

    if (value == 0)
        return zero_repr(buffer);
    if (value < 0) {
        **current = '-';
        (*current)++;
        value = - value;
    }
    fill_buffer(current, value);
    **current = '\0';
}
