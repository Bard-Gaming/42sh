/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_dputstr
*/

#include <mysh/io.h>
#include <mysh/string.h>
#include <unistd.h>


/*
** Tries writing string to given fd.
** If not all bytes were written without error,
** try writing the remaining bytes.
** Does nothing on error / if the message is
** empty.
*/
void sh_dputs(int fd, const char *restrict str)
{
    size_t str_len = sh_strlen(str);
    ssize_t write_size;

    if (str_len == 0)
        return;
    write_size = write(fd, str, str_len);
    if ((size_t)write_size == str_len || write_size < 0)
        return;
    write_size = write(fd, str + write_size, str_len - write_size);
}
