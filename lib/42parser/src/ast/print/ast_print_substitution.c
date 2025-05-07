/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print_substitution
*/

#include <42parser/ast.h>


/*
** Prints a command substitution.
*/
void ast_print_substitution(const ast_t *ast, unsigned short depth)
{
    ast_print_node(ast->data, depth + 1);
}
