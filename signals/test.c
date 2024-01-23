#include "signals.h"
# include "../execute/execute.h"

int	gl_sig = -1;

int	main(int ac, char *argv[])
{
	char		*line;
	t_parser	*parser;
	t_ast		*ast;
	int			status;

	suppress_output();
	while (1)
	{
		signal_handler();
		rl_catch_signals = 0;
		line = readline("msh> ");
		if (!line)
			return (0);
		if (ft_strcmp(line, "") == 0)
		{
			free(line);
			continue;
		}
		parser = parser_init(line);	
		ast = parser_parse(parser);
		status = exe_line(ast);
		ast_destroy(ast);
		free(parser);
		free(line);
	}
	return (0);
}
