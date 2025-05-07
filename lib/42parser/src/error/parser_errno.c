/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_errno_set &&
** parser_errno_get
*/

#include <42parser/error.h>


static parser_errno_t *get_errno_ptr(void)
{
    static parser_errno_t errno = PE_NONE;

    return &errno;
}

/*
** Gets the currently set error
** number.
*/
parser_errno_t parser_errno_get(void)
{
    return *get_errno_ptr();
}

/*
** Sets the current error number to the
** given error.
*/
void parser_errno_set(parser_errno_t error)
{
    parser_errno_t *errno = get_errno_ptr();

    *errno = error;
}

/*
** Sets the current error number to the
** given error, but only if it isn't
** already set to another error.
*/
void parser_errno_set_weak(parser_errno_t error)
{
    parser_errno_t *errno = get_errno_ptr();

    if (*errno == PE_NONE)
        *errno = error;
}
