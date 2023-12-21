NAME = exe
LIBFT = libft.a
SRCS = 	single_cmd/cmd_exe.c \
		single_cmd/child_process.c \
		pipex/pipex_bonus.c \
		pipex/create_pipes_bonus.c \
		pipex/child_process_bonus.c \
		pipex/utils_bonus.c \
		pipex/display_error.c \
		pipex/free_arr.c \
		pipex/path_name.c \
		pipex/execute.c
OBJS = ${SRCS:.c=.o}
FLAGS = -Wall -Werror -Wextra
CC = cc
HEADER = execute.h

%o:%c
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(HEADER)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -L./libft/build -lft

$(LIBFT):
	$(MAKE) -C libft -f Makefile

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: make clean fclean re