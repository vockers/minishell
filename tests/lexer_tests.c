#include <stdio.h>

#include "lexer.h"

int main()
{
	t_token	t;
	char *line = "Hello < world";

	t = get_next_token(line);
	ft_printf("%s\n", t.str);
	t = get_next_token(NULL);
	ft_printf("%s\n", t.str);
	t = get_next_token(NULL);
	ft_printf("%s\n", t.str);

	
	return 0;
}