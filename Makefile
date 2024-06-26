NAME	= minishell
LIBFT	= ./libft/build/libft.a

OBJ_DIR	= .obj

SRCS = 	parser/ast.c \
		parser/lexer_utils.c \
		parser/lexer.c \
		parser/parser.c \
		parser/parser_cmd.c \
		parser/expansion.c \
		execute/builtin_exe.c \
		execute/exe_line.c \
		execute/heredoc_pipe.c \
		execute/heredoc_pipe_utils.c \
		execute/pipex.c \
		execute/display_error.c \
		execute/execute.c \
		execute/exit_handler.c \
		execute/free_arr.c \
		execute/path_name.c \
		execute/file_handler.c \
		signals/signal_handlers.c \
		signals/signal_utils.c \
		builtins/echo.c \
		builtins/cd.c \
		builtins/pwd.c \
		builtins/export.c \
		builtins/unset.c \
		builtins/env.c \
		builtins/exit.c \
		env/env.c \
		env/env_utils.c \
		main/main.c \
		main/minishell.c \

OBJS	= ${SRCS:%.c=$(OBJ_DIR)/%.o}

CC = cc
CFLAGS	= -Wall -Wextra -Werror -Imain -Ilibft -Iparser -Ienv -Ibuiltins -Iexecute -Isignals -fsanitize=address -g

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $^

$(LIBFT):
	$(MAKE) -C libft -f Makefile

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: make clean fclean re
