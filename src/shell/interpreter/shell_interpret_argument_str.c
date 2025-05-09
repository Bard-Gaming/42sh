/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_argument_str
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42sh/string.h>


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
    char *argument_string;

    shell_interpret_argument(ast, data, &arg);
    argument_string = sh_strjoinvec((const char **)arg.data, " ");
    sh_vector_delete(&arg, NULL);
    sh_vector_push_back(argv, argument_string);
}
