/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_readline
*/

#include <readline/terminal.h>
#include <readline/internal.h>
#include <readline/buffer.h>


/*
** Function to return when the
** user sends an end signal
** (i.e. End Of Transmission / EOT)
*/
static char *user_end_signal(void)
{
    rl_terminal_cleanup();
    return NULL;
}

/*
** Yields a line of the user's input,
** in an interactive terminal.
*/
char *rl_terminal_readline(int fd)
{
    ssize_t read_len;
    char input;

    rl_terminal_setup(fd);
    rl_terminal_refresh();
    read_len = read(fd, &input, 1);
    if (read_len != 1 || input == CHAR_EOT)
        return user_end_signal();
    while (read_len == 1 && input != '\n') {
        if (rl_buffer_is_empty() && input == CHAR_EOT)
            return user_end_signal();
        rl_terminal_handle_char(input);
        rl_terminal_refresh();
        read_len = read(fd, &input, 1);
    }
    write(fd, "\n", 1);
    rl_terminal_cleanup();
    return rl_buffer_get_data();
}
