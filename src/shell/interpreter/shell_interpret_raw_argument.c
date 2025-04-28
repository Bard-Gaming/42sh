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
#include <stdlib.h>


/*
** Interprets a raw argument.
**
** No Split:
** Returns a simple string / char buffer that
** needs to be freed by the user.
**
** Split:
** Returns a pointer to an argument vector
** containing a single argument. The data
** within the vector, as well as the vector
** pointer itself, need to be freed by the
** user.
*/
void *shell_interpret_raw_argument(ast_t *ast, sh_data_t *data, int opts)
{
    sh_vector_t *argv;

    (void)data;
    if (!(opts & SH_INTRPT_SPLIT))
        return sh_strdup(ast->data);
    argv = calloc(1, sizeof(sh_vector_t));
    sh_vector_push_back(argv, sh_strdup(ast->data));
    return argv;
}
