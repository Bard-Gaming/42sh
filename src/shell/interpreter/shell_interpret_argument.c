/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_argument
*/

#include <42sh/shell.h>
#include <42parser/ast.h>
#include <string.h>


/*
** Interprets an argument, meaning this
** returns the parsed string (i.e. char *).
** The returned character character string
** must be freed by the user (this is done
** to stay consistent with other nodes).
*/
void *shell_interpret_argument(ast_t *ast, sh_data_t *data)
{
    (void)data;
    return strdup(ast->data);
}
