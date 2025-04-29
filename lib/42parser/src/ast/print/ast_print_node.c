/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print_node
*/

#include <42parser/ast.h>
#include <stdio.h>


static const ast_print_fnc_t node_print_functions[AT_COUNT] = {
    [AT_VARIABLE] = ast_print_variable,
    [AT_SUBSTITUTION] = ast_print_substitution,
    [AT_RAW_ARGUMENT] = ast_print_raw_argument,
    [AT_ARGUMENT_STR] = ast_print_argument,
    [AT_ARGUMENT] = ast_print_argument,
    [AT_COMMAND] = ast_print_container,
    [AT_COMPOUND] = ast_print_container,
    [AT_OPERATION_AND] = ast_print_binary_operation,
    [AT_OPERATION_OR] = ast_print_binary_operation,
    [AT_PIPELINE] = ast_print_container,
    [AT_PROGRAM] = ast_print_container,
};


/*
** Prints a given AST node at the given depth /
** indent level.
*/
void ast_print_node(const ast_t *ast, unsigned short depth)
{
    ast_print_indent(depth);
    puts(ast_strtype(ast));
    if (node_print_functions[ast->type])
        node_print_functions[ast->type](ast, depth);
}
