/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Header file for all
** I/O-related operations
*/

#ifndef MYSH_IO_H
    #define MYSH_IO_H


void sh_dputs(int fd, const char *restrict str);
void sh_putstr(const char *restrict str);
void sh_puterr(const char *restrict msg);


#endif
