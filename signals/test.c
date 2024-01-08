#include "signals.h"
# include "../execute/execute.h"

int	main(int ac, char *argv[], char **envp)
{
	char		*line;
	int			pid;
	t_parser	*parser;
	t_ast		*ast;

	signal_handler_init();
	while (1)
	{
		line = readline("ms> ");
		parser = parser_init(line);	
		ast = parser_parse(parser);
		exe_line(ast, STDIN_FILENO);
		ast_destroy(ast);
		free(parser);
	}
	return (0);
}
