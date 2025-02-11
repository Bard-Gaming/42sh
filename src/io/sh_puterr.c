/*
** EPITECH PROJECT, 2024
** Project - Minishell
** File description:
** Implementation for
** sh_puterr
*/

#include <mysh/io.h>
#include <mysh/string.h>
#include <unistd.h>


/*
** Tries writing msg to stderr.
** If not all bytes were written without error,
** try writing the remaining bytes.
** Does nothing on error / if the message is
** empty.
*/
void sh_puterr(const char *restrict msg)
{
    size_t msg_len = sh_strlen(msg);
    ssize_t write_size;

    if (msg_len == 0)
        return;
    write_size = write(2, msg, msg_len);
    if (write_size == msg_len || write_size < 0)
        return;
    write_size = write(2, msg + write_size, msg_len - write_size);
}
