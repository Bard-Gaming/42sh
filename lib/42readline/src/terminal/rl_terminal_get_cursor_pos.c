/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_get_cursor_pos
*/

#include <readline/terminal.h>


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

    if (read(fd, &input, 1) != 1 || !('0' <= input && input <= '9'))
        return -1;
    result = input - '0';
    while (read(fd, &input, 1) == 1 && '0' <= input && input <= '9')
        result = result * 10 + input - '0';
    return result;
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
    if (read(fd, &input, 1) != 1 || input != '\033')
        return pos;
    if (read(fd, &input, 1) != 1 || input != '[')
        return pos;
    pos.row = integer_from_stream(fd);
    pos.col = integer_from_stream(fd);
    return pos;
}
