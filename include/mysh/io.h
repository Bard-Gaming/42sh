/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all
** I/O-related operations
*/

#ifndef MYSH_IO_H
    #define MYSH_IO_H


void sh_dputs(int fd, const char *restrict str);
void sh_perror(const char *restrict prefix);
void sh_cmd_perror(const char *restrict prefix);


/*
** This utility function is used to write a
** message to the standard output.
*/
static inline void sh_putstr(const char *restrict str)
{
    sh_dputs(1, str);
}

/*
** This utility function is used to write a
** message to the standard error output.
*/
static inline void sh_puterr(const char *restrict err)
{
    sh_dputs(2, err);
}


#endif
