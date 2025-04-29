/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_variable
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/string.h>
#include <42parser/ast.h>


/*
** Interprets a variable.
**
** Returns the value of the variable
** in the form of a string / char buffer.
** If the given variable doesn't have a value,
** an empty string is return instead.
** Either way, the returned string needs to be
** freed by the end user.
*/
#include <stdio.h>
char *shell_interpret_variable(ast_t *ast, sh_data_t *data)
{
    const char *value = sh_data_getvar(data, ast->data);

    printf("name: %s\n", ast->data);
    return sh_strdup(value ?: "");
}
