/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print
*/

#include <42parser/ast.h>
#include <string.h>
#include <stdio.h>



static void print_indent(unsigned short indent_amount)
{
    if (indent_amount == 0)
        return;
    for (unsigned int i = 0; i < indent_amount; i++)
        fputs(" |  ", stdout);
    putchar('\n');
    for (unsigned int i = 0; i < (unsigned)indent_amount - 1; i++)
        fputs(" |  ", stdout);
    fputs(" |- ", stdout);
}

static void print_operation(const ast_t *ast, unsigned short depth)
{
    ast_t **data = ast->data;

    ast_print_node(data[0], depth + 1);
    ast_print_node(data[1], depth + 1);
}

static void print_container(const ast_t *ast, unsigned short depth)
{
    ast_node_buffer_t *buffer = ast->data;

    for (size_t i = 0; i < buffer->count; i++)
        ast_print_node(buffer->nodes[i], depth + 1);
}

static void print_format_arg(const ast_t *ast, unsigned short depth)
{
        print_indent(depth + 1);
        puts("<format arg>");
}

static void print_node_data(const ast_t *ast, unsigned short depth)
{
    switch (ast->type) {
    case AT_ARGUMENT_STR:
    case AT_ARGUMENT:
        return print_format_arg(ast, depth);
    case AT_RAW_ARGUMENT:
        print_indent(depth + 1);
        puts(ast->data);
        return;
    case AT_PIPELINE:
    case AT_PROGRAM:
    case AT_COMMAND:
    case AT_COMPOUND:
        return print_container(ast, depth);
    case AT_OPERATION_AND:
    case AT_OPERATION_OR:
        return print_operation(ast, depth);
    default:
        return;
    }
}

void ast_print_node(const ast_t *ast, unsigned short depth)
{
    print_indent(depth);
    puts(ast_strtype(ast));
    print_node_data(ast, depth);
}

/*
** Recursively print an ast.
*/
void ast_print(const ast_t *ast)
{
    ast_print_node(ast, 0);
    putchar('\n');
}
