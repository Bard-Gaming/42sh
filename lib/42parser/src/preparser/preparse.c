/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** preparse
*/

#include <42parser/preparser.h>
#include <42parser/config.h>
#include <stdlib.h>
#include <string.h>


static bool should_end(const preparser_t *preparser)
{
    return
        preparser->current->type == TT_EOF ||
        preparser->current->type == TT_ERROR;
}

/*
** FIXME: redirects can omit a file coming after
** them if the have a file descriptor.
** Example:
** ">&2 ls" -> ls is an argument, but this function
** doesn't detect it as such.
**
*/
static bool is_argument(const preparser_t *preparser)
{
    return
        preparser->current->type == TT_ARGUMENT &&
        !IS_REDIRECT(preparser->prev->type);
}

static void update_state(preparser_t *preparser)
{
    if (!IS_COMMAND_TOKEN(preparser->current->type)) {
        preparser->is_command = false;
        preparser->has_arg = false;
        return;
    }
    preparser->is_command = true;
    if (is_argument(preparser))
        preparser->has_arg = true;
}

static void add_command_alias(preparser_t *preparser)
{
    parser_config_t *config = parser_config_get();
    const token_t *token = preparser->current;
    char command[token->length + 1];
    char *alias;

    memcpy(command, token->start, token->length);
    command[token->length] = '\0';
    alias = config->substitute(command);
    if (alias == NULL) {
        parser_errno_set(PE_ALIAS_LOOP);
        return;
    }
    preparser_add_str(preparser, alias);
    free(alias);
}

static void preparse_input(preparser_t *preparser)
{
    bool is_not_first;

    while (!should_end(preparser)) {
        is_not_first = preparser->has_arg;
        update_state(preparser);
        if (preparser->has_arg && !is_not_first)
            add_command_alias(preparser);
        else
            preparser_add_token(preparser);
        preparser_add_char(preparser, ' ');
        preparser_next(preparser);
    }
}

/*
** Preparses a given input into an expanded
** one. The resulting buffer needs to be passed
** to free() by the user.
**
** Returns NULL on error.
*/
char *preparse(const char *input)
{
    preparser_t preparser = { 0 };

    preparser_init(&preparser, input);
    preparse_input(&preparser);
    if (P_ERRNO != PE_NONE) {
        free(preparser.output);
        preparser.output = NULL;
    }
    preparser_term(&preparser);
    return preparser.output;
}

/*
** Expands a single pass of the given
** input, skipping the expansion for
** the given command if it appears as
** first statement.
*/
char *preparser_expand(const char *input, const char *command)
{
    preparser_t preparser = { 0 };

    preparser_init(&preparser, input);
    if (token_match(preparser.current, command))
        preparser.has_arg = true;
    preparse_input(&preparser);
    if (P_ERRNO != PE_NONE) {
        free(preparser.output);
        preparser.output = NULL;
    }
    preparser_term(&preparser);
    return preparser.output;
}
