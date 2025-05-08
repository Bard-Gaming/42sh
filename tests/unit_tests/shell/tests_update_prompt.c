/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for update_prompt
** shell
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(update_prompt, .init = init_tests, .fini = end_tests);

Test(update_prompt, full_flag_format_prompt) {
    char *expected_prompt = parse_prompt(" \\u  \\W\\g\\w $", data);
    sh_data_setvar(data, "PS1", " \\u  \\W\\g\\w $");
    shell_update_prompt(data);

    cr_assert_str_eq(data->prompt_str, expected_prompt,
        "FULL FLAG FORMAT PROMPT | Expected to have the right actual prompt and good formating.");
}

Test(update_prompt, raw_format_prompt) {
    char *expected_prompt = parse_prompt(" \\  $", data);
    sh_data_setvar(data, "PS1", " \\  $");
    shell_update_prompt(data);

    cr_assert_str_eq(data->prompt_str, expected_prompt,
        "RAW FORMAT PROMPT | Expected to have the right actual prompt and good formating.");
}
