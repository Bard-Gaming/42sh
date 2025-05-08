/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for
** shell_update_prompt
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <unistd.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(shell_update_prompt, .init = init_tests, .fini = end_tests);

Test(shell_update_prompt, user_prompt) {
    sh_data_setvar(data, "USER", "bobby");
    sh_data_setvar(data, "PS1", "\\u $");
    shell_update_prompt(data);

    cr_assert_str_eq(data->prompt_str, "bobby $",
        "USER PROMPT | Expected \"bobby $\".");
}

Test(shell_update_prompt, cwd_prompt) {
    chdir("/");
    sh_data_setvar(data, "PS1", "\\w \\W $");
    shell_update_prompt(data);

    cr_assert_str_eq(data->prompt_str, "/ / $",
        "CWD PROMPT | Expected \"bobby $\".");
}

Test(shell_update_prompt, cwd_prompt_nontrivial) {
    chdir("/tmp");
    sh_data_setvar(data, "PS1", "\\w \\W $");
    shell_update_prompt(data);

    cr_assert_str_eq(data->prompt_str, "/tmp tmp $",
        "CWD NT PROMPT | Expected \"bobby $\".");
}

Test(shell_update_prompt, raw_format_prompt) {
    sh_data_setvar(data, "PS1", "cool_prompt \\b $");
    shell_update_prompt(data);

    cr_assert_str_eq(data->prompt_str, "cool_prompt \\b $",
        "RAW FORMAT PROMPT | Expected \"cool_prompt \\b $\".");
}
