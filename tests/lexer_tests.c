#include <stdio.h>

#include "lexer.h"

int main()
{
	t_token	t;
	char *line = "\"Hello\" | world|echo>test.txt>>$test<< ...";

	t = get_next_token(line);
	while (t.type != T_NONE)
	{
		ft_printf("%s\n", t.str);
		t = get_next_token(NULL);
	}
	
	return 0;
}
