/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** arguments_is_valid_line
*/

#include <mysh/arguments.h>
#include <stdbool.h>


/*
** Checks whether a given line
** constitutes a valid shell command.
** Invalid commands have unmatched string quotes.
*/
bool arguments_is_valid_line(const char *line)
{
    size_t double_quote_count = 0;
    size_t single_quote_count = 0;

    while (*line != '\0' && *line != '\n') {
        if (*line == '"')
            double_quote_count++;
        if (*line == '\'')
            single_quote_count++;
        line++;
    }
    return
        double_quote_count % 2 == 0 &&
        single_quote_count % 2 == 0;
}
