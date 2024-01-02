#!/bin/bash

case $1 in
	"lexer")
	cc tests/lexer_tests.c parser/lexer.c parser/lexer_utils.c libft/build/libft.a -I./libft -I./parser
	./a.out
	;;
	"parser")
	cc tests/parser_tests.c parser/ast.c parser/lexer.c parser/lexer_utils.c parser/parser.c libft/build/libft.a -I./libft -I./parser
	./a.out
	;;
esac