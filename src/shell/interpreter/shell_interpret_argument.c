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
#include <42sh/data.h>
#include <42parser/ast.h>
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
    char *str = shmalloc((len + 1) * sizeof(char));
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
** Parses an argument into an argument vector.
*/
static sh_vector_t parse_argument(ast_argument_t *raw_arg, sh_data_t *data)
{
    sh_vector_t parsed_arg = { 0 };

    sh_vector_push_back(&parsed_arg, argument_to_string(raw_arg, data));
    return parsed_arg;
}

/*
** Interprets an argument.
** Due to argument splitting, this
** function returns a argument vector.
*/
void *shell_interpret_argument(ast_t *ast, sh_data_t *data)
{
    ast_argument_t *raw_arg = ast->data;
    sh_vector_t *argv = shcalloc(1, sizeof(sh_vector_t));
    sh_vector_t parsed_arg = parse_argument(raw_arg, data);

    sh_vector_append_range(argv, &parsed_arg);
    sh_vector_delete(&parsed_arg, NULL);
    return argv;
}
