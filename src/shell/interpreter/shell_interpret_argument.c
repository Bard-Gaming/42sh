/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_argument
*/

#include <42sh/shell.h>
#include <42sh/memory.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42parser/ast.h>


static sh_vector_t parse_argument(ast_argument_t *raw_arg, sh_data_t *data)
{
    sh_vector_t result = { 0 };
    char *current;

    for (size_t i = 0; i < raw_arg->length; i++) {
        if (raw_arg->data[i].is_string) {
            sh_vector_push_back(&result, sh_strdup(raw_arg->data[i].val.str));
            continue;
        }
        current = shell_interpret_value(raw_arg->data[i].val.node, data);
        sh_vector_push_back(&result, current);
    }
    return result;
}

/*
** Interprets a format argument.
**
** This function returns a string / character buffer
** that holds the computed value of the argument.
*/
char *shell_interpret_argument(ast_t *ast, sh_data_t *data)
{
    ast_argument_t *raw_arg = ast->data;
    sh_vector_t argument_components = parse_argument(raw_arg, data);
    char *result = sh_strjoinvec((const char **)argument_components.data);

    sh_vector_delete(&argument_components, NULL);
    return result;
}
