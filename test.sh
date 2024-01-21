#!/bin/bash

case $1 in
	"lexer")
	cc tests/lexer_tests.c parser/lexer.c parser/lexer_utils.c libft/build/libft.a -I./libft -I./parser -fsanitize=address -g && ./a.out
	;;
	"parser")
	export TEST_VAR=h3ll0_w0rld
	cc tests/parser_tests.c parser/ast.c parser/lexer.c parser/lexer_utils.c parser/parser.c parser/expansion.c libft/build/libft.a -I./libft -I./parser -fsanitize=address -g && ./a.out
	;;
	"builtins")
	cc tests/builtins_tests.c builtins/cd.c builtins/echo.c builtins/pwd.c builtins/export.c env/env.c env/env_utils.c libft/build/libft.a -I. -I./libft -I./env -I./builtins -fsanitize=address -g && ./a.out
	;;
	"env")
	cc tests/env_tests.c builtins/env.c env/env.c libft/build/libft.a -I./libft -I./builtins -I./env -fsanitize=address -g && ./a.out
	;;
esac