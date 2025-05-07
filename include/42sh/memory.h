/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Header file for all of Multishell's
** memory allocation functions
*/

#ifndef SHELL_MEMORY_H
    #define SHELL_MEMORY_H

    #define _NO_RETURN __attribute__((noreturn))
    #define SH_CRITICAL_MEMFAIL 51

    #include <stddef.h>


void *shmalloc(size_t size);
void *shcalloc(size_t nmemb, size_t size);
void *shrealloc(void *ptr, size_t size);
void *shreallocarray(void *ptr, size_t nmemb, size_t size);

void sh_memory_failure(void) _NO_RETURN;


#endif
