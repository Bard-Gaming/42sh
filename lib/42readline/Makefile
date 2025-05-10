##
## EPITECH PROJECT, 2024
## Project - readline
## File description:
## Makefile used to help
## and facilitate the compilation
## of the readline library
##

CC = gcc
CFLAGS =

NAME = libreadline.a

INCLUDE_DIRS = -I./include

SRC_FILES =	src/readline.c											\
			src/readline_configure.c								\
			src/readline_free.c										\
			src/readline_is_active.c								\
			src/buffer/rl_buffer_add_char.c							\
			src/buffer/rl_buffer_empty.c							\
			src/buffer/rl_buffer_get.c								\
			src/buffer/rl_buffer_get_data.c							\
			src/buffer/rl_buffer_grow.c								\
			src/buffer/rl_buffer_insert_char.c						\
			src/buffer/rl_buffer_is_empty.c							\
			src/buffer/rl_buffer_print.c							\
			src/buffer/rl_buffer_replace_char.c						\
			src/buffer/rl_buffer_rm_char.c							\
			src/buffer/rl_buffer_set.c								\
			src/config/rl_config_get.c								\
			src/internal/rl_get_word.c								\
			src/internal/rl_get_word_end.c							\
			src/internal/rl_get_word_length.c						\
			src/internal/rl_get_word_start.c						\
			src/internal/rl_is_control_char.c						\
			src/internal/rl_is_word_char.c							\
			src/internal/rl_readline_file.c							\
			src/internal/rl_state_get.c								\
			src/terminal/rl_terminal_add_char.c						\
			src/terminal/rl_terminal_autocomplete.c					\
			src/terminal/rl_terminal_autocomplete_long.c			\
			src/terminal/rl_terminal_cleanup.c						\
			src/terminal/rl_terminal_clear.c						\
			src/terminal/rl_terminal_get.c							\
			src/terminal/rl_terminal_get_cursor_pos.c				\
			src/terminal/rl_terminal_handle_char.c					\
			src/terminal/rl_terminal_handle_control_char.c			\
			src/terminal/rl_terminal_next_word.c					\
			src/terminal/rl_terminal_prev_word.c					\
			src/terminal/rl_terminal_readline.c						\
			src/terminal/rl_terminal_refresh.c						\
			src/terminal/rl_terminal_set_cursor_pos.c				\
			src/terminal/rl_terminal_set_cursor_col.c				\
			src/terminal/rl_terminal_setup.c						\

OBJ_FILES = $(SRC_FILES:%.c=%.o)

.PHONY = all debug sanitize clean fclean re _no_repo

all: $(NAME)

%.o: %.c
	@$(CC) -c $< $(INCLUDE_DIRS) $(CFLAGS) -o $@

$(NAME): $(OBJ_FILES)
	@ar rc $(NAME) $(OBJ_FILES)

debug: CFLAGS += -ggdb -Wall -Wextra
debug: fclean $(NAME)

sanitize: CFLAGS += -g -static-libasan -fsanitize=address
sanitize: fclean $(NAME)

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

_no_repo:
	@rm -f LICENSE
	@rm -f README.md
	@rm -rf .git
