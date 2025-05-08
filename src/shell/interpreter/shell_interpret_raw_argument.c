/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_raw_argument
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42parser/ast.h>


/*
** Interprets a raw argument.
**
** Returns a simple string / char buffer that
** needs to be freed by the user.
*/
void shell_interpret_raw_argument(ast_t *ast,
    UNUSED sh_data_t *data, sh_vector_t *argv)
{
    sh_vector_push_back(argv, sh_strdup(ast->data));
}
