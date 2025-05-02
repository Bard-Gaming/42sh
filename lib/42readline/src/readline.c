/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline
*/

#include <readline.h>
#include <readline/buffer.h>
#include <readline/internal.h>
#include <termios.h>
#include <unistd.h>


static bool should_continue(int fd, ssize_t read_len, char c)
{
    if (read_len < 0)
        return false;
    if (isatty(fd) && c == '\n')
        return false;
    return read_len != 0;
}

static char *error(void)
{
    *rl_state_get() = false;
    return NULL;
}

/*
** Empty buffer
** store the first state of the line
** Disable canonical mode
*/
static void setup_readline(int fd, struct termios *tty, const char *prompt)
{
    rl_buffer_empty();
    rl_buffer_update_prompt(prompt);
    *rl_state_get() = true;
    rl_disable_canonical_mode(fd, tty);
}

char *readline(int fd, const char *prompt)
{
    struct termios tty;
    ssize_t read_len;
    char input;

    setup_readline(fd, &tty, prompt);
    rl_buffer_print(fd);
    read_len = read(fd, &input, 1);
    if (read_len <= 0)
        return error();
    while (should_continue(fd, read_len, input)) {
        if (rl_handle_control_chars(&input, &read_len, fd))
            continue;
        rl_buffer_add_char(input);
        rl_buffer_print(fd);
        read_len = read(fd, &input, 1);
    }
    write(fd, "\n", 1);
    *rl_state_get() = false;
    rl_restore_canonical_mode(&tty);
    return rl_buffer_get_data();
}
