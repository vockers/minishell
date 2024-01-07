#include <stdarg.h>
#include <stdio.h>
#include <assert.h>
#include "lexer.h"

void ft_assert_str(char *line, const char *str1, const char *str2)
{
	if (str1 == NULL || str2 == NULL)
		return ;
	if (ft_strcmp(str1, str2) != 0)
	{
		ft_printf("%s\nlexer value: %s, expected: %s\n", line, str1, str2);
		assert(ft_strcmp(str1, str2) == 0);
	}
}

void	test_lexer(char *line)
{
	t_token	t;

	t = get_next_token(line);
	while (t.type != T_NONE)
	{
		ft_printf("%s\n", t.str);
		t = get_next_token(NULL);
	}
	ft_printf("-------------------\n");
}

void	assert_lexer(char *line, ...)
{
	va_list	ap;
	t_token	t;

	va_start(ap, line);
	t = get_next_token(line);
	while (t.type != T_NONE)
	{
		ft_assert_str(line, t.str, va_arg(ap, char *));
		t = get_next_token(NULL);
	}
	va_end(ap);
}

int	main(void)
{
	// test_lexer("\"Hello\" | world|echo>test.txt>>$test<< ...");
	// test_lexer("\" hello\t\" | '\"world\"' > \"'\"");
	assert_lexer("\" hello\t\" | '\"world\"' > \"'\"", "\" hello\t\"", "|", "'\"world\"'", ">", "\"'\"");
	assert_lexer("\"hello|world\"", "\"hello|world\"");
	ft_printf("All tests passed!\n");
	return (0);
}
