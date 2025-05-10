/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Header file for everything
** related to error handling
*/

#ifndef PARSER_ERROR_H
    #define PARSER_ERROR_H
    #define P_ERRNO parser_errno_get()


typedef enum {
    PE_NONE,

    PE_ILLEGAL_CHAR,
    PE_ILLEGAL_VAR_NAME,
    PE_WRONG_SYNTAX,
    PE_NULL_COMMAND,
    PE_UNMATCHED_RAW_STRING,
    PE_UNMATCHED_FORMAT_STRING,
    PE_UNMATCHED_BACKTICK,
    PE_UNMATCHED_LBRACE,
    PE_UNMATCHED_RPAREN,
    PE_UNMATCHED_LPAREN,
    PE_MISSING_REDIRECT_NAME,
    PE_MISSING_THEN_ENDIF,
    PE_IF_EXPRESSION_SYNTAX,
    PE_IF_MISSING_BRACE,
    PE_WHILE_NO_ARGS,
    PE_WHILE_MISSING_BRACE,
    PE_WHILE_MISSING_END,
    PE_FOREACH_NO_ARGS,
    PE_FOREACH_MISSING_END,
    PE_REDIRECT_WITH_ILLEGAL_FD,
    PE_EMPTY_HEREDOC,
    PE_EMPTY_HERESTR,
    PE_ALIAS_LOOP,

    PE_COUNT,
} parser_errno_t;


// Errno manip:
void parser_errno_set(parser_errno_t error);
void parser_errno_set_weak(parser_errno_t error);
parser_errno_t parser_errno_get(void);

// Errno utils:
void parser_perror(const char *prefix);
void parser_critical_error(void) __attribute__((noreturn));


#endif
