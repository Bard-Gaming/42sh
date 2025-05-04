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

SRC_FILES =	src/readline.c								\
			src/readline_configure.c					\
			src/readline_free.c							\
			src/readline_is_active.c					\
			src/buffer/rl_buffer_add_char.c				\
			src/buffer/rl_buffer_empty.c				\
			src/buffer/rl_buffer_get.c					\
			src/buffer/rl_buffer_get_data.c				\
			src/buffer/rl_buffer_is_tty_end.c			\
			src/buffer/rl_buffer_print.c				\
			src/buffer/rl_buffer_rm_char.c				\
			src/buffer/rl_buffer_update_prompt.c		\
			src/internal/rl_disable_canonical_mode.c	\
			src/internal/rl_handle_control_char.c		\
			src/internal/rl_is_control_char.c			\
			src/internal/rl_readline_file.c				\
			src/internal/rl_readline_tty.c				\
			src/internal/rl_restore_canonical_mode.c	\
			src/internal/rl_state_get.c					\

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
