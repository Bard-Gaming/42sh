/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Header file for function
*/

#ifndef LIB_READLINE_H
    #define LIB_READLINE_H
    #include <stdbool.h>
    #include <stddef.h>


typedef char *(*autocomplete_fnc_t)(const char *);
typedef void (*long_autocomplete_fnc_t)(const char *);
typedef char *(*history_fnc_t)(size_t);


/*
** Read a line from the given file stream.
** If the stream is a tty, arrow/cursor
** control keys are handled appropriately.
** The output is a heap-allocated string of
** characters, which needs to be freed by the
** user. If an error occurs, NULL is returned
** instead.
*/
char *readline(int fd, const char *prompt);

/*
** Determines whether or not input is being
** asked from the user. This is especially
** useful when multiple things happen at once,
** i.e. when dealing with signals for instance.
*/
bool readline_is_active(void);

/*
** Free the internal buffer allocated
** by the readline library.
*/
void readline_free(void);


/*
** Configure the readline library.
** This function needs to be called before
** any other, as this sets up the library.
** All parameters are nullable, and will take
** default values when NULL.
*/
void readline_configure(
    autocomplete_fnc_t autocomplete,
    long_autocomplete_fnc_t autocomplete_long,
    history_fnc_t history);


#endif
