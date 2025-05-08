/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_print_columns
*/

#include <42sh/io.h>
#include <string.h>
#include <stdio.h>


/*
** Prints the argument vector with
** spaces between each argument.
*/
static void print_spaced(char **argv)
{
    sh_putstr(argv[0]);
    argv++;
    while (*argv != NULL) {
        printf(" %s", *argv);
        argv++;
    }
    putchar('\n');
}

/*
** Retrieves the length of the
** longest argument within argv.
*/
size_t get_max_length(char **argv)
{
    size_t max_length = strlen(argv[0]);
    size_t current_length;

    argv++;
    while (*argv != NULL) {
        current_length = strlen(*argv);
        if (current_length > max_length)
            max_length = current_length;
        argv++;
    }
    return max_length;
}

/*
** Prints a single line of the argument
** vector.
*/
static void print_line(char ***argv, int max_length, unsigned int max_count)
{
    printf("%-*s", max_length, **argv);
    (*argv)++;
    for (unsigned int i = 1; **argv != NULL && i < max_count - 1; i++) {
        printf(" %-*s", max_length, **argv);
        (*argv)++;
    }
    if (**argv == NULL) {
        putchar('\n');
        return;
    }
    printf(" %-*s\n", max_length, **argv);
    (*argv)++;
}

/*
** Prints an argument vector in
** columns.
*/
void sh_print_columns(char **argv, int columns)
{
    size_t max_length;
    unsigned int element_count;

    if (argv[0] == NULL)
        return;
    if (columns <= 0)
        return print_spaced(argv);
    max_length = get_max_length(argv);
    element_count = columns / (max_length + 1);
    while (*argv != NULL)
        print_line(&argv, max_length, element_count);
}
