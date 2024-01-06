#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>

#include "parser.h"

void ft_assert_str(char *line, const char *str1, const char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return ;
	if (ft_strcmp(str1, str2) != 0)
	{
		ft_printf("%s\nparser value: %s, expected: %s\n", line, str1, str2);
		assert(ft_strcmp(str1, str2) == 0);
	}
}

void ft_assert_type(char *line, int t1, int t2)
{
	if (t1 != t2)
	{
		ft_printf("%s\nparser value: %d, expected: %d\n", line, t1, t2);
		assert(t1 == t2);
	}
}

void vassert_ast(char *line, t_ast *ast, va_list ap)
{
	char		*value;
	enum e_ast	type;

	if (ast == NULL)
		return ;

	type = va_arg(ap, int);
	value = va_arg(ap, char *);
	ft_assert_type(line, ast->type, type);
	ft_assert_str(line, ast->value, value);
	vassert_ast(line, ast->left, ap);
	vassert_ast(line, ast->right, ap);
}

void test_ast(char *line, ...)
{
	va_list		ap;
	t_parser	*parser;
	t_ast		*ast;

	parser = parser_init(line);	
	ast = parser_parse(parser);
	va_start(ap, line);

	vassert_ast(line, ast, ap);

	va_end(ap);
	ast_destroy(ast);
	free(parser);
}

int main()
{
	test_ast("test11 test12 test13", 
		AST_ARG, "test11",
		AST_ARG, "test12",
		AST_ARG, "test13"
	);

	test_ast("hello | world test",
		AST_PIPE, "|",
		AST_ARG, "hello",
		AST_ARG, "world",
		AST_ARG, "test"
	);

	test_ast("hello | world test | cat",
		AST_PIPE, "|",
		AST_ARG, "hello",
		AST_PIPE, "|",
		AST_ARG, "world",
		AST_ARG, "test",
		AST_ARG, "cat"
	);

	test_ast("hello | world test | cat | wc",
		AST_PIPE, "|",
		AST_ARG, "hello",
		AST_PIPE, "|",
		AST_ARG, "world",
		AST_ARG, "test",
		AST_PIPE, "|",
		AST_ARG, "cat",
		AST_ARG, "wc"
	);

	test_ast("ls > test",
		AST_ARG, "ls",
		AST_GRT, ">",
		AST_ARG, "test"
	);

	test_ast("> test ls",
		AST_ARG, "ls",
		AST_GRT, ">",
		AST_ARG, "test"
	);
	
	test_ast("> test ls > test1",
		AST_ARG, "ls",
		AST_GRT, ">",
		AST_ARG, "test",
		AST_GRT, ">",
		AST_ARG, "test1"
	);

	test_ast("> test > test1 ls > test2",
		AST_ARG, "ls",
		AST_GRT, ">",
		AST_ARG, "test",
		AST_GRT, ">",
		AST_ARG, "test1",
		AST_GRT, ">",
		AST_ARG, "test2"
	);

	test_ast("< test wc",
		AST_ARG, "wc",
		AST_LSR, "<",
		AST_ARG, "test"
	);

	test_ast("< test < test1 wc",
		AST_ARG, "wc",
		AST_LSR, "<",
		AST_ARG, "test",
		AST_LSR, "<",
		AST_ARG, "test1"
	);
	test_ast("wc < test",
		AST_ARG, "wc",
		AST_LSR, "<",
		AST_ARG, "test"
	);

	test_ast("< test < test1 wc < test2 < test3",
		AST_ARG, "wc",
		AST_LSR, "<",
		AST_ARG, "test",
		AST_LSR, "<",
		AST_ARG, "test1",
		AST_LSR, "<",
		AST_ARG, "test2",
		AST_LSR, "<",
		AST_ARG, "test3"
	);

	test_ast("wc << EOF",
		AST_ARG, "wc",
		AST_HEREDOC, "<<",
		AST_ARG, "EOF"
	);

	test_ast("wc << EOF > test",
		AST_ARG, "wc",
		AST_HEREDOC, "<<",
		AST_ARG, "EOF",
		AST_GRT, ">",
		AST_ARG, "test"
	);

	test_ast("< test wc << EOF > test1",
		AST_ARG, "wc",
		AST_LSR, "<",
		AST_ARG, "test",
		AST_HEREDOC, "<<",
		AST_ARG, "EOF",
		AST_GRT, ">",
		AST_ARG, "test1"
	);

	test_ast("< test wc >> test1",
		AST_ARG, "wc",
		AST_LSR, "<",
		AST_ARG, "test",
		AST_APPEND, ">>",
		AST_ARG, "test1"
	);

	test_ast("'hello' \">\" \"'world'\"",
		AST_ARG, "hello",
		AST_ARG, ">",
		AST_ARG, "'world'"
	);

	test_ast("\"hello $TEST_VAR world\"",
		AST_ARG, "hello h3ll0_w0rld world"
	);

	ft_printf("All tests passed!\n");
	
	return (0);
}