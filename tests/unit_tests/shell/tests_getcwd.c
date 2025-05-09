/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for get_cwd
** shell
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <unistd.h>
#include <pwd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(shell_getcwd, .init = init_tests, .fini = end_tests);

Test(shell_getcwd, basic_path) {
    char *expected_path = capture_stdout("echo \"$PWD\" | sed \"s|^$HOME|~|\"");
    expected_path[strlen(expected_path) - 1] = '\0';
    char *path = shell_getcwd(data, 0);

    cr_assert_str_eq(expected_path, path,
        "BASIC PATH GETCWD | Expected path with this formating : '~Desktop/path/...'");
}

Test(shell_getcwd, basename_path) {
    char *path = shell_getcwd(data, 1);
    char *excepted_path = capture_stdout("basename \"$PWD\"");
    strtok(excepted_path, "\n");

    cr_assert_str_eq(path, excepted_path,
        "BASENAME PATH GETCWD | Expected this path : '42sh'");
}

Test(shell_getcwd, home_path) {
    struct passwd *user_info = getpwuid(getuid());
    char *user_home = user_info->pw_dir;
    chdir(user_home);

    char *path = shell_getcwd(data, 0);

    cr_assert_str_eq(path, "~",
        "HOME PATH GETCWD | Expected this path : '~'");
}
