/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_autocomplete_long
*/

#include <readline/terminal.h>
#include <readline/internal.h>
#include <readline/buffer.h>
#include <readline/config.h>
#include <stdlib.h>


/*
** Applies a long autocompletion on the
** currently selected word.
*/
void rl_terminal_autocomplete_long(void)
{
    readline_config_t *config = rl_config_get();
    terminal_t *terminal = rl_terminal_get();
    char *selected_word = rl_get_word(
        rl_buffer_get_data(), terminal->cursor_index
    );

    write(terminal->fd, "\n", 1);
    config->autocomplete_long(selected_word);
    terminal->start_col = rl_terminal_get_cursor_pos(terminal->fd).col;
    free(selected_word);
}
