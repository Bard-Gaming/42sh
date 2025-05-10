/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_get_cursor_pos
*/

#include <readline/terminal.h>
#include <stdbool.h>


/*
** Turns the characters retrieved from
** the stream into an integer. This
** stops at the first occurrence of a
** non-integer character.
*/
static int integer_from_stream(int fd)
{
    char input;
    int result;

    if (read(fd, &input, 1) != 1)
        return -1;
    if (!('0' <= input && input <= '9')) {
        rl_terminal_handle_char(input);
        return -1;
    }
    result = input - '0';
    while (read(fd, &input, 1) == 1 && '0' <= input && input <= '9')
        result = result * 10 + input - '0';
    return result;
}

/*
** Reads all characters until the given
** character is reached, or nothing is
** left to be read. If the given character
** is found, true is returned.
** TODO: Skip chars if terminal isn't in
** use.
*/
static bool read_char(int fd, char c)
{
    char input;

    while (read(fd, &input, 1) == 1) {
        if (input == c)
            return true;
        rl_terminal_handle_char(input);
    }
    return false;
}

/*
** Retrieves the position of the
** terminal's cursor.
** Returns a negative value if the
** given coordinate is invalid.
*/
cursor_pos_t rl_terminal_get_cursor_pos(int fd)
{
    cursor_pos_t pos = { -1, -1 };
    char input;

    SEND_CODE_FD(fd, CURSOR_REQUEST_POS);
    if (!read_char(fd, '\033'))
        return pos;
    if (read(fd, &input, 1) != 1)
        return pos;
    if (input != '[') {
        rl_terminal_handle_char('\033');
        return pos;
    }
    pos.row = integer_from_stream(fd);
    pos.col = integer_from_stream(fd);
    return pos;
}
