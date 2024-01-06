#include <stdio.h>

#include "lexer.h"

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

int	main(void)
{
	test_lexer("\"Hello\" | world|echo>test.txt>>$test<< ...");
	test_lexer("\" hello\t\" | '\"world\"' > \"'\"");
	return (0);
}
