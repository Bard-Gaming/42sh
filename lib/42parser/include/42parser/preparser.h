/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Header file for 42parser's
** preparser
*/

#ifndef PARSER_PREPARSER_H
    #define PARSER_PREPARSER_H
    #include <42parser/lexer.h>

    #define PREPARSER_GROWTH_FACTOR 2
    #define PREPARSER_INIT_CAP 20


typedef struct {
    lexer_t lexer;
    token_t *prev;
    token_t *current;

    // State:
    bool is_command;
    bool has_arg;

    // Output:
    char *output;
    size_t count;
    size_t capacity;
} preparser_t;


// Preparse entry:
char *preparse(const char *input);
char *preparser_expand(const char *input, const char *command);

// Preparse utils:
void preparser_init(preparser_t *preparser, const char *input);
void preparser_next(preparser_t *preparser);
void preparser_term(preparser_t *preparser);
void preparser_grow(preparser_t *preparser);

// Preparse output:
void preparser_add_char(preparser_t *preparser, char c);
void preparser_add_str(preparser_t *preparser, const char *str);
void preparser_add_token(preparser_t *preparser);


#endif
