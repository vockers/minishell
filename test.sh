#!/bin/bash

case $1 in
	"lexer")
	echo "test"
	;;
	"parser")
	cc tests/parser_tests.c parser/ast.c parser/lexer.c parser/parser.c libft/build/libft.a -I./libft -I./parser
	./a.out
	;;
	*)
	echo "hoi"
	;;
esac