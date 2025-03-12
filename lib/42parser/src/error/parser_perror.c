/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_perror
*/

#include <42parser/error.h>
#include <unistd.h>


static const char *p_strerror(void)
{
    static const char *err_messages[PE_COUNT] = {
        "No error set.",
        "Use of illegal char.",
        "Syntax error.",
        "Unmatched parenthesis.",
    };

    return err_messages[P_ERRNO];
}

static size_t msg_len(const char *msg)
{
    size_t msg_len;

    for (msg_len = 0; msg[msg_len] != '\0'; msg_len++);
    return msg_len;
}

/*
** Writes the current error message
** (defined in P_ERRNO) in a specific format.
** If the given prefix is NULL, only the error
** message is written.
*/
void parser_perror(const char *prefix)
{
    const char *error_msg = p_strerror();

    if (prefix != NULL) {
        write(STDERR_FILENO, prefix, msg_len(prefix));
        write(STDERR_FILENO, ": ", 2);
    }
    write(STDERR_FILENO, error_msg, msg_len(error_msg));
    write(STDERR_FILENO, "\n", 2);
}
