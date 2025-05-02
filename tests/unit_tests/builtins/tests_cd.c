/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for cd
** builtin
*/

#include <42sh/builtins.h>
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
    cr_redirect_stdout();
}

static void end_tests(void)
{
    sh_data_delete(data);
}


TestSuite(builtin_cd, .init = init_tests, .fini = end_tests);


Test(builtin_cd, move_to_existing_directory) {
    char *args[] = { "cd", "/tmp", NULL };
    int exit_value = builtin_cd(args, data);
    char cur_path[1024];

    getcwd(cur_path, sizeof(cur_path));
    cr_assert_str_eq(cur_path, "/tmp",
        "MOVE TO VALID DIR | Expected for current dir : /tmp");
    cr_assert_eq(exit_value, 0,
        "MOVE TO VALID DIR | Expected for return value : 0");
}

Test(builtin_cd, move_to_invalid_directory) {
    char *args[] = {"cd", "/wrongdir", NULL};
    int exit_value = builtin_cd(args, data);

    cr_assert_stderr_eq_str("/wrongdir: No such file or directory.\n",
        "MOVE TO INVALID DIR | Expected for error message : '/wrongdir: No such file or directory.'");
    cr_assert_eq(exit_value, 1,
        "MOVE TO INVALID DIR | Expected for return value : 1");
}

Test(builtin_cd, too_many_args) {
    char *args[] = {"cd", "arg1", "arg2", NULL};
    int exit_value = builtin_cd(args, data);

    cr_assert_stderr_eq_str("cd: Too many arguments.\n",
        "TOO MANY ARGS | Expected for error message : 'cd: Too many arguments.'");
    cr_assert_eq(exit_value, 2,
        "TOO MANY ARGS | Expected for return value : 1");
}

Test(builtin_cd, empty_args) {
    char *args[] = {"cd", NULL};
    int exit_value = builtin_cd(args, data);
    char cur_path[1024];
    const char *home_path = sh_data_getvar(data, "HOME");

    getcwd(cur_path, sizeof(cur_path));
    cr_assert_str_eq(cur_path, home_path,
        "EMPTY ARGS | Expected for current dir : %s", home_path);
    cr_assert_eq(exit_value, 0,
        "EMPTY ARGS | Expected for return value : 0");
}

Test(builtin_cd, previous_path) {
    char *args[] = {"cd", "/tmp", NULL};
    char old_path[1024];
    char cur_path[1024];
    int exit_value;

    getcwd(old_path, sizeof(old_path));
    builtin_cd(args, data);
    args[1] = "-";
    exit_value = builtin_cd(args, data);
    getcwd(cur_path, sizeof(cur_path));
    cr_assert_str_eq(cur_path, old_path,
        "PREVIOUS PATH | Expected for current dir : %s", old_path);
    cr_assert_eq(exit_value, 0,
        "PREVIOUS PATH | Expected for return value : 0");
}
