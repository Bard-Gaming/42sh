/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for run_rc
** shell
*/

#include "../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(run_rc, .init = init_tests, .fini = end_tests);

Test(run_rc, basic_run_rc) {
    char rc_path[256];
    snprintf(rc_path, sizeof(rc_path), "%s%s", sh_data_getvar(data, "HOME"), SHELL_RC_PATH);
    FILE *rc_file = fopen(rc_path, "w");
    if (rc_file) {
        fprintf(rc_file, "echo test");
        fclose(rc_file);
    }
    shell_run_rc(data);

    fflush(stdout);
    cr_assert_stdout_eq_str("test\n",
        "BASIC RUN RC | Expected the right output corresponding to the command in the rc file.");
}
