/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_raw_argument
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42parser/ast.h>
#include <stdlib.h>
#include <string.h>


/*
** Interprets a raw argument.
** Raw arguments are normal arguments that
** aren't interpreted in any way, meaning all
** characters present will be taken literally.
** This returns a pointer to a vector, as this
** is required to achieve the same return values
** as the shell_interpret_argument() function.
*/
void *shell_interpret_raw_argument(ast_t *ast, sh_data_t *data)
{
    sh_vector_t *argv = calloc(1, sizeof(sh_vector_t));

    (void)data;
    sh_vector_push_back(argv, strdup(ast->data));
    return argv;
}
