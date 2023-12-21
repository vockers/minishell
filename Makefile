NAME = exe
LIBFT = libft.a
SRCS = cmd_exe.c execute.c pathname.c
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