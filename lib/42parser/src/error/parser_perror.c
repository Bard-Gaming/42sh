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
    [PE_ILLEGAL_VAR_NAME] = "Illegal variable name.",
    [PE_WRONG_SYNTAX] = "Syntax error.",
    [PE_NULL_COMMAND] = "Invalid null command.",
    [PE_UNMATCHED_RAW_STRING] = "Unmatched '''.",
    [PE_UNMATCHED_FORMAT_STRING] = "Unmatched '\"'.",
    [PE_UNMATCHED_BACKTICK] = "Unmatched '`'.",
    [PE_UNMATCHED_RPAREN] = "Too many )'s.",
    [PE_UNMATCHED_LPAREN] = "Too many ('s.",
    [PE_MISSING_REDIRECT_NAME] = "Missing name for redirect.",
    [PE_MISSING_THEN_ENDIF] = "then: then/endif not found.",
    [PE_REDIRECT_WITH_ILLEGAL_FD] = "Redirect with illegal file descriptor.",
    [PE_EMPTY_HEREDOC] = "Missing end sequence to heredoc.",
    [PE_EMPTY_HERESTR] = "Missing string for herestring.",
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
