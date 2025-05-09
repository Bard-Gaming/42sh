/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_argument
*/

#include <42sh/shell.h>
#include <42sh/symbols.h>
#include <42sh/memory.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42parser/ast.h>
#include <string.h>
#include <stdlib.h>


/*
** Joins the last element of <a> with the first
** element of <b> and returns the result.
** Both the elements are removed from the vectors.
*/
static char *join_ends(sh_vector_t *a, sh_vector_t *b)
{
    char *end = sh_vector_pop(a, a->count - 1);
    char *start = sh_vector_pop(b, 0);
    char *result = sh_strjoin(end, start);

    free(end);
    free(start);
    return result;
}

/*
** Adds the interpreted result of the node
** into the given argument vector.
*/
static void add_node(ast_t *node, sh_data_t *data, sh_vector_t *arg)
{
    sh_vector_t node_result = { 0 };

    shell_interpret_value(node, data, &node_result);
    if (node_result.count == 0)
        return;
    if (arg->count == 0)
        return sh_vector_move(arg, &node_result);
    sh_vector_push_back(arg, join_ends(arg, &node_result));
    sh_vector_move(arg, &node_result);
}

/*
** Adds the given string to the given
** argument vector.
*/
static void add_string(const char *str, sh_vector_t *arg)
{
    char *last_arg;
    char *joined_element;

    if (arg->count == 0)
        return sh_vector_push_back(arg, sh_strdup(str));
    last_arg = arg->data[arg->count - 1];
    joined_element = sh_strjoin(last_arg, str);
    free(last_arg);
    arg->data[arg->count - 1] = joined_element;
}

/*
** Interprets an argument.
**
** This interprets all sub nodes and adds them to an
** owned vector, then merges the components into a
** single argument, which is then added to the main
** argument vector.
*/
void shell_interpret_argument(ast_t *ast,
    sh_data_t *data, sh_vector_t *argv)
{
    ast_argument_t *raw_arg = ast->data;
    sh_vector_t arg = { 0 };

    for (size_t i = 0; i < raw_arg->length; i++) {
        if (raw_arg->data[i].is_string) {
            add_string(raw_arg->data[i].val.str, &arg);
            continue;
        }
        add_node(raw_arg->data[i].val.node, data, &arg);
    }
    sh_vector_glob(&arg, sh_data_getvar(data, "globskipdots"));
    sh_vector_move(argv, &arg);
}
