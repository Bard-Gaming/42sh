/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_variable
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42parser/ast.h>


/*
** Interprets a variable.
**
** Adds the value of the given variable
** to the last element of the argument vector.
*/
void shell_interpret_variable(ast_t *ast, sh_data_t *data, sh_vector_t *argv)
{
    char *value = sh_strdup(sh_data_getvar(data, ast->data) ?: "");

    sh_vector_push_back(argv, value);
}
