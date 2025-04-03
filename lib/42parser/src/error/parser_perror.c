/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_perror
*/

#include <42parser/error.h>
#include <unistd.h>


static const char *error_messages[PE_COUNT] = {
    [PE_NONE] = "No error set.",

    [PE_ILLEGAL_CHAR] = "Use of illegal char.",
    [PE_WRONG_SYNTAX] = "Syntax error.",
    [PE_NULL_COMMAND] = "Invalid null command.",
    [PE_UNMATCHED_PARENTHESIS] = "Unmatched parenthesis.",
    [PE_MISSING_FILE] = "Expected file path.",
    [PE_APPEND_REDIRECT_WITH_FD] = "Illegal append redirect with fd.",
};

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
    const char *error_msg = error_messages[P_ERRNO];

    if (prefix != NULL) {
        write(2, prefix, msg_len(prefix));
        write(2, ": ", 2);
    }
    write(2, error_msg, msg_len(error_msg));
    write(2, "\n", 1);
}
