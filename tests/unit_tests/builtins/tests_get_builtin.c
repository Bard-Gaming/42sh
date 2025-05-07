/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Unit tests for get_builtin
** builtin
*/

#include <42sh/builtins.h>
#include <42sh/symbols.h>
#include <42sh/data.h>
#include <42sh/tests.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>


extern sh_data_t *data;


TestSuite(builtin_get_builtin, .init = init_tests, .fini = end_tests);

Test(builtin_get_builtin, get_alias) {
    builtin_cmd_t excepted_builtin = builtin_alias;
    builtin_cmd_t result_builtin = sh_get_builtin("alias");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET ALIAS BUILTIN | Expected to return the function of builtin alias.");
}

Test(builtin_get_builtin, get_cd) {
    builtin_cmd_t excepted_builtin = builtin_cd;
    builtin_cmd_t result_builtin = sh_get_builtin("cd");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET CD BUILTIN | Expected to return the function of builtin cd.");
}

Test(builtin_get_builtin, get_env) {
    builtin_cmd_t excepted_builtin = builtin_env;
    builtin_cmd_t result_builtin = sh_get_builtin("env");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET ENV BUILTIN | Expected to return the function of builtin env.");
}

Test(builtin_get_builtin, get_exec) {
    builtin_cmd_t excepted_builtin = builtin_exec;
    builtin_cmd_t result_builtin = sh_get_builtin("exec");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET EXEC BUILTIN | Expected to return the function of builtin exec.");
}

Test(builtin_get_builtin, get_exit) {
    builtin_cmd_t excepted_builtin = builtin_exit;
    builtin_cmd_t result_builtin = sh_get_builtin("exit");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET EXIT BUILTIN | Expected to return the function of builtin exit.");
}

Test(builtin_get_builtin, get_reload) {
    builtin_cmd_t excepted_builtin = builtin_reload;
    builtin_cmd_t result_builtin = sh_get_builtin("reload");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET RELOAD BUILTIN | Expected to return the function of builtin reload.");
}

Test(builtin_get_builtin, get_repeat) {
    builtin_cmd_t excepted_builtin = builtin_repeat;
    builtin_cmd_t result_builtin = sh_get_builtin("repeat");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET REPEAT BUILTIN | Expected to return the function of builtin repeat.");
}

Test(builtin_get_builtin, get_set) {
    builtin_cmd_t excepted_builtin = builtin_set;
    builtin_cmd_t result_builtin = sh_get_builtin("set");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET SET BUILTIN | Expected to return the function of builtin set.");
}

Test(builtin_get_builtin, get_setenv) {
    builtin_cmd_t excepted_builtin = builtin_setenv;
    builtin_cmd_t result_builtin = sh_get_builtin("setenv");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET SETENV BUILTIN | Expected to return the function of builtin setenv.");
}

Test(builtin_get_builtin, get_unalias) {
    builtin_cmd_t excepted_builtin = builtin_unalias;
    builtin_cmd_t result_builtin = sh_get_builtin("unalias");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET UNALIAS BUILTIN | Expected to return the function of builtin unalias.");
}

Test(builtin_get_builtin, get_unset) {
    builtin_cmd_t excepted_builtin = builtin_unset;
    builtin_cmd_t result_builtin = sh_get_builtin("unset");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET UNSET BUILTIN | Expected to return the function of builtin unset.");
}

Test(builtin_get_builtin, get_unsetenv) {
    builtin_cmd_t excepted_builtin = builtin_unsetenv;
    builtin_cmd_t result_builtin = sh_get_builtin("unsetenv");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET UNSETENV BUILTIN | Expected to return the function of builtin unsetenv.");
}

Test(builtin_get_builtin, get_version) {
    builtin_cmd_t excepted_builtin = builtin_version;
    builtin_cmd_t result_builtin = sh_get_builtin("version");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET VERSION BUILTIN | Expected to return the function of builtin version.");
}

Test(builtin_get_builtin, get_where) {
    builtin_cmd_t excepted_builtin = builtin_where;
    builtin_cmd_t result_builtin = sh_get_builtin("where");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET WHERE BUILTIN | Expected to return the function of builtin where.");
}

Test(builtin_get_builtin, get_which) {
    builtin_cmd_t excepted_builtin = builtin_which;
    builtin_cmd_t result_builtin = sh_get_builtin("which");

    cr_assert_eq(excepted_builtin, result_builtin,
        "GET WHICH BUILTIN | Expected to return the function of builtin which.");
}

Test(builtin_get_builtin, wrong_get_un) {
    builtin_cmd_t result_builtin = sh_get_builtin("un");

    cr_assert_eq(result_builtin, NULL,
        "WRONG GET UN | Expected to return NULL for unexistant builtin 'un'.");
}

Test(builtin_get_builtin, wrong_get_unseti) {
    builtin_cmd_t result_builtin = sh_get_builtin("unseti");

    cr_assert_eq(result_builtin, NULL,
        "WRONG GET UNSETI | Expected to return NULL for unexistant builtin 'unseti'.");
}

Test(builtin_get_builtin, wrong_get_seti) {
    builtin_cmd_t result_builtin = sh_get_builtin("seti");

    cr_assert_eq(result_builtin, NULL,
        "WRONG GET SETI | Expected to return NULL for unexistant builtin 'seti'.");
}

Test(builtin_get_builtin, wrong_get_re) {
    builtin_cmd_t result_builtin = sh_get_builtin("re");

    cr_assert_eq(result_builtin, NULL,
        "WRONG GET RE | Expected to return NULL for unexistant builtin 're'.");
}

Test(builtin_get_builtin, wrong_get_e) {
    builtin_cmd_t result_builtin = sh_get_builtin("e");

    cr_assert_eq(result_builtin, NULL,
        "WRONG GET E | Expected to return NULL for unexistant builtin 'e'.");
}

Test(builtin_get_builtin, wrong_get_ex) {
    builtin_cmd_t result_builtin = sh_get_builtin("ex");

    cr_assert_eq(result_builtin, NULL,
        "WRONG GET EX | Expected to return NULL for unexistant builtin 'ex'.");
}

Test(builtin_get_builtin, wrong_get_wh) {
    builtin_cmd_t result_builtin = sh_get_builtin("wh");

    cr_assert_eq(result_builtin, NULL,
        "WRONG GET WH | Expected to return NULL for unexistant builtin 'wh'.");
}
