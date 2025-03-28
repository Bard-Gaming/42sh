/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Header file for function
*/

#ifndef LIB_READLINE_H
    #define LIB_READLINE_H


/*
** Read a line from the given file stream.
** If the stream is a tty, arrow/cursor
** control keys are handled appropriately.
** The output is a heap-allocated string of
** characters, which needs to be freed by the
** user. If an error occurs, NULL is returned
** instead.
*/
char *readline(int fd);

/*
** Free the internal buffer allocated
** by the readline library.
*/
void readline_free(void);


#endif
