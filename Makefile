NAME	= minishell
LIBFT	= libft.a

OBJ_DIR	= .obj

SRCS = 	parser/ast.c \
		parser/lexer_utils.c \
		parser/lexer.c \
		parser/parser.c \
		parser/expansion.c \
		execute/builtin_exe.c \
		execute/exe_line.c \
		execute/heredoc_pipe.c \
		execute/heredoc_pipe_utils.c \
		execute/pipex.c \
		execute/display_error.c \
		execute/execute.c \
		execute/free_arr.c \
		execute/path_name.c \
		execute/file_handler.c \
		signals/signal_handlers.c \
		signals/signal_utils.c \
		builtins/echo.c \
		builtins/exit.c \
		builtins/pwd.c \
		env/env.c \
		env/env_utils.c \
		main/main.c \
		main/minishell.c \

OBJS = ${SRCS:%.c=$(OBJ_DIR)/%.o}
CFLAGS = -Ilibft -Iparser -Ienv -Ibuiltins -Iexecute -Isignals
CC = cc

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lreadline -L./libft/build -lft

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
