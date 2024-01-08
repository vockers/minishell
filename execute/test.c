#include "execute.h"

int	main(int ac, char *argv[])
{
	t_parser	*parser;
	t_ast		*ast;

	if (ac < 2)
		return (0);
	parser = parser_init(argv[1]);	
	ast = parser_parse(parser);
	exe_line(ast, STDIN_FILENO);
	ast_destroy(ast);
	free(parser);
	return (0);
}