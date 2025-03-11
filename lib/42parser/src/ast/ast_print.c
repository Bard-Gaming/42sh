/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_print
*/

#include <42parser/ast.h>
#include <unistd.h>


static void print_indent(unsigned short indent_amount)
{
    const char *indent_line = " |- ";

    if (indent_amount == 0)
        return;
    for (unsigned int i = 0; i < indent_amount; i++)
        write(1, " |  ", 4);
    write(1, "\n", 1);
    for (unsigned int i = 0; i < indent_amount - 1; i++)
        write(1, " |  ", 4);
    write(1, indent_line, 4);
}

static void print_type(ast_type_t type)
{
    size_t type_len;
    static const char *type_str[AT_COUNT] = {
        "Error", "Command",
        "Unary <&>", "Operation <;>",
        "Operation <&>", "Operation <&&>",
        "Operation <|>", "Operation <||>",
    };

    for (type_len = 0; type_str[type][type_len] != '\0'; type_len++);
    write(1, type_str[type], type_len);
    write(1, "\n", 1);
}

static void print_command(const ast_t *ast)
{
    ast_command_t *data = ast->data;
    size_t arg_len;

    for (size_t i = 0; i < data->arg_count; i++) {
        for (arg_len = 0; data->args[i][arg_len] != '\0'; arg_len++);
        write(1, data->args[i], arg_len);
        write(1, i + 1 == data->arg_count ? "\n" : " ", 1);
    }
}

static void print_operation(const ast_t *ast, unsigned short depth)
{
    ast_t **data = ast->data;

    ast_print_node(data[0], depth + 1);
    ast_print_node(data[1], depth + 1);
}

static void print_node_data(const ast_t *ast, unsigned short depth)
{
    switch (ast->type) {
    case AT_COMMAND:
        print_indent(depth + 1);
        print_command(ast);
        return;
    case AT_COMMAND_CHAIN:
    case AT_OPERATION_PIPE:
    case AT_OPERATION_AND:
    case AT_OPERATION_JOB:
    case AT_OPERATION_OR:
        return print_operation(ast, depth);
    default:
        return;
    }
}

void ast_print_node(const ast_t *ast, unsigned short depth)
{
    print_indent(depth);
    print_type(ast->type);
    print_node_data(ast, depth);
}

/*
** Recursively print an ast.
*/
void ast_print(const ast_t *ast)
{
    ast_print_node(ast, 0);
}
