/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_handle_control_char
*/

#include <readline/terminal.h>
#include <readline/internal.h>
#include <readline/buffer.h>
#include <readline/config.h>
#include <stdlib.h>


/*
** Autocompletes the currently selected
** argument.
*/
static void handle_tabulation(terminal_t *terminal)
{
    terminal->tab_count++;
    if (terminal->tab_count < AUTOCOMPLETE_LONG_CUTOFF)
        return rl_terminal_autocomplete();
    return rl_terminal_autocomplete_long();
}

/*
** Moves the cursor by the given offset.
*/
static void move_cursor(terminal_t *terminal, int offset)
{
    string_buffer_t *buffer = rl_buffer_get();
    ssize_t new_index = terminal->cursor_index + offset;

    terminal->cursor_index = CLAMP(0, new_index, buffer->count);
}

/*
** Moves to the history index by the given
** offset, and sets the buffer to the history
** entry at that new index.
*/
static void move_history(terminal_t *terminal, int offset)
{
    readline_config_t *config = rl_config_get();
    size_t new_index = MAX(0, (ssize_t)terminal->history_index + offset);
    char *history_entry;

    if (new_index == 0) {
        terminal->history_index = 0;
        rl_terminal_clear();
        return;
    }
    history_entry = config->history(new_index);
    if (history_entry == NULL)
        return;
    terminal->history_index = new_index;
    rl_buffer_set(history_entry);
    terminal->cursor_index = strlen(history_entry);
    free(history_entry);
}

/*
** Same as the move_history() function,
** except that this does so with an
** offset 5 times greater.
*/
static void move_page(terminal_t *terminal, char key)
{
    int offset = key == '5' ? 5 : -5;
    char input;

    if (read(terminal->fd, &input, 1) != 1 || input != '~')
        return;
    move_history(terminal, offset);
}

static void delete_next(terminal_t *terminal)
{
    char input;

    if (read(terminal->fd, &input, 1) != 1)
        return;
    if (input != '~')
        return;
    rl_buffer_rm_char(terminal->cursor_index);
}

static void handle_ctrl_sequence(terminal_t *terminal, char key)
{
    switch (key) {
    case 'A':
    case 'B':
        return move_history(terminal, key == 'A' ? 5 : -5);
    case 'C':
        return rl_terminal_next_word();
    case 'D':
        return rl_terminal_prev_word();
    }
}

static void handle_ctrl(terminal_t *terminal)
{
    char input;

    if (read(terminal->fd, &input, 1) != 1)
        return;
    if (input != ';')
        return;
    if (read(terminal->fd, &input, 1) != 1)
        return;
    if (input != '5')
        return;
    if (read(terminal->fd, &input, 1) != 1)
        return;
    handle_ctrl_sequence(terminal, input);
}

static void handle_escape_sequence(terminal_t *terminal, char key)
{
    switch (key) {
    case 'A':
    case 'B':
        return move_history(terminal, key == 'A' ? 1 : -1);
    case 'C':
    case 'D':
        return move_cursor(terminal, key == 'C' ? 1 : -1);
    case '1':
        return handle_ctrl(terminal);
    case '3':
        return delete_next(terminal);
    case '5':
    case '6':
        return move_page(terminal, key);
    }
}

/*
** Handles the given control character
** approriately.
*/
void rl_terminal_handle_control_char(char c)
{
    terminal_t *terminal = rl_terminal_get();

    switch (c) {
    case CHAR_DEL:
        if (terminal->cursor_index == 0)
            return;
        terminal->cursor_index--;
        return rl_buffer_rm_char(terminal->cursor_index);
    case '\033':
        if (read(terminal->fd, &c, 1) != 1)
            return;
        if (c != '[')
            return rl_terminal_add_char(c);
        if (read(terminal->fd, &c, 1) != 1)
            return;
        return handle_escape_sequence(terminal, c);
    case '\t':
        return handle_tabulation(terminal);
    }
}
