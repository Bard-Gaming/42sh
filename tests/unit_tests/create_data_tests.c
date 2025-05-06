/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** create_data_tests
*/

#include <42sh/data.h>
#include <criterion/redirect.h>

extern char **environ;
sh_data_t *data = NULL;

void init_tests(void)
{
    data = sh_data_from_unix_env(environ);
    cr_redirect_stderr();
    cr_redirect_stdout();
}

void init_tests_debug(void)
{
    data = sh_data_from_unix_env(environ);
}

void end_tests(void)
{
    sh_data_delete(data);
}
