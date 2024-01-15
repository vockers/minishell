#!/bin/bash

case $1 in
	"lexer")
	cc tests/lexer_tests.c parser/lexer.c parser/lexer_utils.c libft/build/libft.a -I./libft -I./parser -fsanitize=address -g
	./a.out
	;;
	"parser")
	export TEST_VAR=h3ll0_w0rld
	cc tests/parser_tests.c parser/ast.c parser/lexer.c parser/lexer_utils.c parser/parser.c parser/expansion.c libft/build/libft.a -I./libft -I./parser -fsanitize=address -g
	./a.out
	;;
	"builtins")
	cc tests/builtins_tests.c builtins/echo.c builtins/pwd.c builtins/export.c libft/build/libft.a -I./libft -I./builtins -fsanitize=address -g
	./a.out
	;;
	"env")
	cc tests/env_tests.c env/env.c libft/build/libft.a -I./libft -I./env -fsanitize=address -g
	./a.out
	;;
esac