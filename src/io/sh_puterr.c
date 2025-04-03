/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_puterr
*/

#include <mysh/io.h>


void sh_puterr(const char *restrict msg)
{
    sh_dputs(2, msg);
}
