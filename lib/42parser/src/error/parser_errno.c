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

parser_errno_t parser_errno_get(void)
{
    return *get_errno_ptr();
}

void parser_errno_set(parser_errno_t error)
{
    parser_errno_t *errno = get_errno_ptr();

    *errno = error;
}
