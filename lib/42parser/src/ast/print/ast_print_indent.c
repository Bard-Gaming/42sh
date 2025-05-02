/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print_indent
*/

#include <42parser/ast.h>
#include <stdio.h>


/*
** Utility function to print an indent of
** the given level.
*/
void ast_print_indent(unsigned short indent_level)
{
    if (indent_level == 0)
        return;
    for (unsigned int i = 0; i < indent_level; i++)
        fputs(" |  ", stdout);
    putchar('\n');
    for (unsigned int i = 0; i < (unsigned)indent_level - 1; i++)
        fputs(" |  ", stdout);
    fputs(" |- ", stdout);
}
