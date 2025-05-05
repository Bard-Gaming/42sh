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


/*
** Interprets a format argument string.
**
** This interprets all sub nodes and adds them to an
** owned vector, then merges the components into a
** single argument, which is then added to the main
** argument vector.
*/
void shell_interpret_argument_str(ast_t *ast,
    sh_data_t *data, sh_vector_t *argv)
{
    sh_vector_t arg = { 0 };
    ast_argument_t *raw_arg = ast->data;
    char *argument_str;

    for (size_t i = 0; i < raw_arg->length; i++) {
        if (raw_arg->data[i].is_string) {
            sh_vector_push_back(&arg, sh_strdup(raw_arg->data[i].val.str));
            continue;
        }
        shell_interpret_value(raw_arg->data[i].val.node, data, &arg);
    }
    sh_vector_glob(&arg, sh_data_getvar(data, "globskipdots"));
    argument_str = sh_strjoinvec((const char **)arg.data, "");
    sh_vector_push_back(argv, argument_str);
    sh_vector_delete(&arg, NULL);
}
