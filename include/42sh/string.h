/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all things
** related to memory strings
*/

#ifndef SHELL_STRING_H
    #define SHELL_STRING_H

    #define ITOA_MAX 12

    #define COLOR_YELLOW "\033[1;93m"
    #define COLOR_GREEN  "\033[1;92m"
    #define COLOR_BLUE   "\033[1;94m"
    #define COLOR_RED    "\033[1;91m"
    #define COLOR_RESET  "\033[0m"

    #define _YLW(txt) COLOR_YELLOW txt COLOR_RESET
    #define _GRN(txt) COLOR_GREEN txt COLOR_RESET
    #define SHELL_PROMPT _GRN(" \\u ") _YLW(" \\W") "\\g $ "

    #include <stdbool.h>


char *sh_basename(const char *restrict path);
void sh_itoa(char *str, int value);
void sh_strappend(char **dest, const char *restrict ref);
char *sh_strdup(const char *restrict ref);
bool sh_strisname(const char *restrict str, const char *restrict prefix);
bool sh_strisnum(const char *repr);
char *sh_strjoin(const char *restrict a, const char *restrict b);
char *sh_strjoinvec(const char **argv, const char *sep);


#endif
