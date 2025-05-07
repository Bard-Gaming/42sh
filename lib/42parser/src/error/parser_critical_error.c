/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_critical_error
*/

#include <42parser/error.h>
#include <stdlib.h>
#include <stdio.h>


/*
** This function is used by the library
** when an unrecoverable error is encountered.
*/
void parser_critical_error(void)
{
    fputs("42parser: critical memory error\n", stderr);
    exit(84);
}
