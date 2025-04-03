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
void sh_putstr(const char *restrict str);
void sh_puterr(const char *restrict msg);
void sh_perror(const char *prefix);
void sh_cmd_perror(const char *prefix);


#endif
