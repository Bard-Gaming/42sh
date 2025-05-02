/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_readline_tty
*/

#include <readline/internal.h>
#include <readline/buffer.h>


/*
** Empty buffer
** store the first state of the line
** Disable canonical mode
*/
static void setup_readline(int fd, struct termios *tty, const char *prompt)
{
    rl_buffer_empty();
    rl_disable_canonical_mode(fd, tty);
    rl_buffer_update_prompt(prompt);
    rl_buffer_print(fd);
}

static char *user_end(struct termios *tty)
{
    rl_restore_canonical_mode(tty);
    return NULL;
}

/*
** Readline function for an interactive
** file descriptor.
*/
char *rl_readline_tty(int fd, const char *prompt)
{
    struct termios tty;
    ssize_t read_len;
    char input;

    setup_readline(fd, &tty, prompt);
    read_len = read(fd, &input, 1);
    if (read_len <= 0 || input == CHAR_EOT)
        return user_end(&tty);
    while (read_len > 0 && input != '\n') {
        if (rl_buffer_is_tty_end(input))
            return user_end(&tty);
        if (rl_handle_control_chars(&input, &read_len, fd))
            continue;
        rl_buffer_add_char(input);
        rl_buffer_print(fd);
        read_len = read(fd, &input, 1);
    }
    write(fd, "\n", 1);
    rl_restore_canonical_mode(&tty);
    return rl_buffer_get_data();
}
