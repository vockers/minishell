#!/bin/bash

case $1 in
	"lexer")
	cc tests/lexer_tests.c parser/lexer.c parser/lexer_utils.c libft/build/libft.a -I./libft -I./parser -g
	./a.out
	;;
	"parser")
	export TEST_VAR=h3ll0_w0rld
	cc tests/parser_tests.c parser/ast.c parser/lexer.c parser/lexer_utils.c parser/parser.c parser/expansion.c libft/build/libft.a -I./libft -I./parser
	./a.out
	;;
esac