/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_history
*/

#include <42sh/shell.h>
#include <42sh/string.h>
#include <42sh/io.h>
#include <stdlib.h>
#include <stdio.h>


/*
** Skips all entries between 1 and the
** given start.
** The length parameter is given, as it
** is used to determines whether or not
** the EOF has been reached after this
** function call or not.
*/
static void skip_entries(FILE *file, size_t start, ssize_t *len)
{
    char *entry = NULL;
    size_t capacity = 0;

    for (size_t i = 1; *len > 0 && i < start; i++)
        *len = getline(&entry, &capacity, file);
    free(entry);
}

/*
** Computes the start index based on
** the given argument.
** Returns false if the given argument
** can't be represented by a number,
** and true if it can.
*/
static bool get_start(size_t *start, const char *arg)
{
    size_t entry_count;
    size_t arg_value;

    if (!sh_strisnum(arg))
        return false;
    entry_count = shell_history_count();
    arg_value = strtoul(arg, NULL, 10);
    *start = arg_value >= entry_count ?
        1 : entry_count - arg_value + 1;
    return true;
}

/*
** Function to return when an invalid
** number was given as argument.
*/
static int invalid_number(void)
{
    sh_puterr("history: Badly formed number.\n");
    return 1;
}

/*
** Function to return when too many arguments
** are given to the command.
*/
static int too_many_args(void)
{
    sh_puterr("history: Too many arguments.\n");
    return 1;
}

/*
** Main function to display history.
** This function is split from the main
** one to be able to close the given history
** file, irregardless of if an error has occured
** or not.
*/
int display_history(FILE *history_file, char *args[])
{
    size_t start = 1;
    char *entry = NULL;
    size_t capacity = 0;
    ssize_t read_len = 1;

    if (args[1] != NULL && args[2] != NULL)
        return too_many_args();
    if (args[1] != NULL && !get_start(&start, args[1]))
        return invalid_number();
    if (history_file == NULL)
        return 0;
    skip_entries(history_file, start, &read_len);
    read_len = getline(&entry, &capacity, history_file);
    for (size_t i = start; read_len > 0; i++) {
        printf(" %lu %s", i, entry);
        read_len = getline(&entry, &capacity, history_file);
    }
    free(entry);
    return 0;
}

/*
** Implementation for the shell's builtin
** history command.
** This command displays the user's command
** history. If no arguments are given, this
** displays all history entries. If a valid
** number is given, this displays the last
** n entries.
*/
int builtin_history(char *args[], UNUSED sh_data_t *data)
{
    FILE *history_file = shell_history_open("rt");
    int status;

    status = display_history(history_file, args);
    if (history_file != NULL)
        fclose(history_file);
    return status;
}
