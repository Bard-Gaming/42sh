/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all things
** related to memory strings
*/

#ifndef MYSH_STRING_H
    #define MYSH_STRING_H
    #include <stdlib.h>


size_t sh_strlen(const char *restrict str);
char *sh_strjoin(const char *restrict a, const char *restrict b);

// String Duplication:
char *sh_strdup(const char *restrict str);
char *sh_strndup(const char *restrict str, size_t end);

// String Comparison:
int sh_strcmp(const char *restrict a, const char *restrict b);
int sh_strncmp(const char *restrict a, const char *restrict b, size_t n);
char *sh_strchr(const char *str, char c);

// String Copying:
char *sh_strcpy(char *dest, const char *ref);


#endif
