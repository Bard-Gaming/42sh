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
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern char **environ;


static void init_tests(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static void end_tests(void)
{
}

static char *get_env_output(const sh_symbols_t *table)
{
    char *output = NULL;
    char *line = NULL;
    size_t line_len;
    size_t size = 0;

    for (size_t i = 0; i < table->capacity; i++) {
        if (table->data[i].name == NULL)
            continue;
        asprintf(&line, "%s=%s\n", table->data[i].name, table->data[i].value);
        line_len = strlen(line);
        output = realloc(output, (size + line_len + 1) * sizeof(char));
        strcpy(output + size, line);
        size += line_len;
        free(line);
    }
    return output;
}


TestSuite(builtin_env, .init = init_tests, .fini = end_tests);


Test(builtin_env, verify_env_is_valid) {
    sh_data_t *data = sh_data_from_unix_env(environ);
    char *args[] = { "env", NULL };
    char *expected_output = get_env_output(data->env);
    int exit_value = builtin_env(args, data);

    fflush(stdout);
    cr_assert_stdout_eq_str(expected_output,
        "VALID ENV | Expected valid environment variables.");
    cr_assert_eq(exit_value, 0,
        "VALID ENV | Expected return value 0");
    sh_data_delete(data);
}

Test(builtin_env, too_many_args) {
    sh_data_t *data = sh_data_from_unix_env(environ);
    char *args[] = { "env", "arg", NULL };
    int exit_value = builtin_env(args, data);

    cr_assert_stderr_eq_str("env: Too many arguments.\n",
        "TOO MANY ARGS | Expected for error message : 'env: Too many arguments.'");
    cr_assert_eq(exit_value, 2,
        "TOO MANY ARGS | Expected return value 2");
    sh_data_delete(data);
}
