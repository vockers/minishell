#include "signals.h"
# include "../execute/execute.h"

int	gl_sig = -1;

int	main(int ac, char *argv[])
{
	char		*line;
	t_parser	*parser;
	t_ast		*ast;

	while (1)
	{
		signal_handler();
		line = readline("ms> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, "") == 0)
		{
			free(line);
			continue;
		}
		parser = parser_init(line);	
		ast = parser_parse(parser);
		exe_line(ast);
		ast_destroy(ast);
		free(parser);
		free(line);
	}
	return (0);
}
