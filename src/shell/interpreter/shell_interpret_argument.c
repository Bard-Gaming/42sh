/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_argument
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42parser/ast.h>
#include <stdlib.h>
#include <string.h>


/*
** Counts the aggregate length of every
** character within the argument.
*/
static size_t count_arg_len(const ast_argument_t *arg, sh_data_t *data)
{
    const char *value;
    size_t len = 0;

    for (size_t i = 0; i < arg->length; i++) {
        if (arg->data[i].is_char) {
            len++;
            continue;
        }
        value = sh_data_getvar(data, arg->data[i].val.var);
        if (value == NULL)
            continue;
        len += strlen(value);
    }
    return len;
}

/*
** Copies a variable's value into
** the given destination string.
*/
static char *cpy_value(char *dest, const char *variable, sh_data_t *data)
{
    const char *value = sh_data_getvar(data, variable);

    if (value == NULL)
        return dest;
    return stpcpy(dest, value);
}

/*
** Converts an argument buffer to a
** string, converting all variable
** names to their values.
*/
static char *argument_to_string(const ast_argument_t *arg, sh_data_t *data)
{
    size_t len = count_arg_len(arg, data);
    char *str = malloc((len + 1) * sizeof(char));
    char *current = str;

    for (size_t i = 0; i < arg->length; i++) {
        if (!arg->data[i].is_char) {
            current = cpy_value(current, arg->data[i].val.var, data);
            continue;
        }
        *current = arg->data[i].val.c;
        current++;
    }
    *current = '\0';
    return str;
}

/*
** Interprets an argument, meaning this
** returns the parsed string (i.e. char *).
** The returned character character string
** must be freed by the user (this is done
** to stay consistent with other nodes).
*/
void *shell_interpret_argument(ast_t *ast, sh_data_t *data)
{
    ast_argument_t *arg = ast->data;

    return argument_to_string(arg, data);
}
