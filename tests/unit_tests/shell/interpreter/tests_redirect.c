/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for redirections
** shell
*/

#include "../../tests.h"
#include <42sh/data.h>
#include <42sh/shell.h>
#include <42sh/builtins.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <unistd.h>


extern sh_data_t *data;


TestSuite(shell_redirect, .init = init_tests, .fini = end_tests);

Test(shell_redirect, output_file_path_redirect) {
    char *excepted_output = capture_stdout("whoami");
    shell_system("whoami > test_file1", data);
    system("cat test_file1");
    system("rm test_file1");

    cr_assert_stdout_eq_str(excepted_output,
        "OUTPUT FILE PATH REDIRECT | Expected to have same output of official command in the test file.");
}

Test(shell_redirect, output_file_descriptor_redirect) {
    char *excepted_output = capture_stdout("whoami");
    shell_system("whoami 1>&2", data);

    cr_assert_stderr_eq_str(excepted_output,
        "OUTPUT FILE DESCRIPTOR REDIRECT | Expected to have same output of official command in the stderr.");
}

Test(shell_redirect, here_string_redirect) {
    shell_system("cat <<< 'hello !'", data);

    cr_assert_stdout_eq_str("hello !\n",
        "HERE STRING REDIRECT | Expected to have same output of input string.");
}

Test(shell_redirect, here_doc_redirect) {

    int saved_stdin = dup(STDIN_FILENO);
    FILE *tmp = tmpfile();
    fputs("hello !\nEOF\n", tmp);
    rewind(tmp);
    dup2(fileno(tmp), STDIN_FILENO);
    shell_system("cat << EOF", data);
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);

    cr_assert_stdout_eq_str("hello !\n",
        "HERE DOC REDIRECT | Expected to have same output of input string.");
}

Test(shell_redirect, input_file_path_redirect) {
    char *excepted_output = capture_stdout("whoami");
    shell_system("whoami > test_file2", data);
    shell_system("cat < test_file2", data);
    system("rm test_file2");

    cr_assert_stdout_eq_str(excepted_output,
        "INPUT FILE PATH REDIRECT | Expected to have same output of official command in the test file.");
}

Test(shell_redirect, output_file_path_redirect_appending) {
    char *excepted_output = capture_stdout("whoami ; whoami");
    shell_system("whoami > test_file3", data);
    shell_system("whoami >> test_file3", data);
    system("cat test_file3");
    system("rm test_file3");

    cr_assert_stdout_eq_str(excepted_output,
        "OUTPUT FILE PATH REDIRECT APPENDING | Expected to have same output of official command in the test file.");
}
