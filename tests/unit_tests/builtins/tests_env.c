/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for env
** builtin
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


extern char **environ;
static sh_data_t *data;


static void init_tests(void)
{
    data = sh_data_from_unix_env(environ);
    cr_redirect_stderr();
}

static void end_tests(void)
{
    sh_data_delete(data);
}

char *get_env_output(const sh_symbols_t *table)
{
    char *output = NULL;
    char *line = NULL;
    size_t line_len;
    size_t size = 0;

    for (size_t i = 0; i < table->capacity; i++) {
        if (table->data[i].name == NULL)
            continue;
        line = NULL;
        asprintf(&line, "%s%s%s\n", table->data[i].name, "=", table->data[i].value);
        line_len = strlen(line);
        char *new_output = realloc(output, size + line_len + 1);
        output = new_output;
        memcpy(output + size, line, line_len);
        size += line_len;
        output[size] = '\0';
        free(line);
    }
    return output;
}


TestSuite(builtin_env, .init = init_tests, .fini = end_tests);

Test(builtin_env, verify_env_is_valid) {
    char *args[] = {"env", NULL};
    char *expected_output = get_env_output(data->env);
    int exit_value = builtin_env(args, data);

    cr_assert_stdout_eq_str(expected_output,
        "VALID ENV | Expected the valids env variables.");
    cr_assert_eq(exit_value, 0,
        "VALID ENV | Expected for return value : 0");
}

Test(builtin_env, too_many_args) {
    char *args[] = {"env", "arg", NULL};
    int exit_value = builtin_env(args, data);

    cr_assert_stderr_eq_str("env: Too many arguments.\n",
        "TOO MANY ARGS | Expected for error message : 'env: Too many arguments.'");
    cr_assert_eq(exit_value, 1,
        "TOO MANY ARGS | Expected for return value : 1");
}
