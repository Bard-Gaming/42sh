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
    PE_WRONG_SYNTAX,
    PE_UNMATCHED_PARENTHESIS,

    PE_COUNT,
} parser_errno_t;


void parser_errno_set(parser_errno_t error);
parser_errno_t parser_errno_get(void);
void parser_perror(const char *prefix);


#endif
