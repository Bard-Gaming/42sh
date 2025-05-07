/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for tests
*/

#ifndef INCLUDED_TESTS_H
    #define INCLUDED_TESTS_H


char *capture_stdout(const char *command);
char *capture_stdout_tcsh(const char *command);
void init_tests(void);
void init_tests_debug(void);
void end_tests(void);


#endif
