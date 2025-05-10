/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_autocomplete
*/

#include <readline/terminal.h>
#include <readline/internal.h>
#include <readline/buffer.h>
#include <readline/config.h>
#include <stdlib.h>


/*
** Replaces the word currently selected in the
** terminal with the one given as parameter.
*/
static void replace_word(terminal_t *terminal, const char *replacement)
{
    size_t current_len = rl_get_word_length(
        rl_buffer_get_data(), terminal->cursor_index
    );

    if (current_len >= strlen(replacement))
        return;
    terminal->tab_count = 0;
    terminal->cursor_index =
        rl_get_word_end(rl_buffer_get_data() + terminal->cursor_index) -
        rl_buffer_get_data();
    for (size_t i = current_len; replacement[i] != '\0'; i++)
        rl_terminal_add_char(replacement[i]);
}

/*
** Autocompletes the select word
** in the argument buffer.
*/
void rl_terminal_autocomplete(void)
{
    terminal_t *terminal = rl_terminal_get();
    readline_config_t *config = rl_config_get();
    char *autocompleted_word;
    char *selected_word = rl_get_word(
        rl_buffer_get_data(), terminal->cursor_index
    );

    autocompleted_word = config->autocomplete(selected_word);
    free(selected_word);
    if (autocompleted_word == NULL)
        return;
    replace_word(terminal, autocompleted_word);
    free(autocompleted_word);
}
