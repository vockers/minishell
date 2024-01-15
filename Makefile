NAME = minishell
LIBFT = libft.a
SRCS = 	parser/ast.c \
		parser/lexer_utils.c \
		parser/lexer.c \
		parser/parser.c \
		execute/exe_line.c \
		execute/heredoc_pipe.c \
		signals/test.c \
		execute/pipex.c \
		execute/display_error.c \
		execute/execute.c \
		execute/free_arr.c \
		execute/path_name.c \
		execute/file_handler.c \
		signals/signal_handlers.c

OBJS = ${SRCS:.c=.o}
FLAGS = -Wall -Werror -Wextra
CC = cc

%o:%c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -lreadline -L./libft/build -lft

$(LIBFT):
	$(MAKE) -C libft -f Makefile

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: make clean fclean re
