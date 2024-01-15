#include "signals.h"
# include "../execute/execute.h"

int	gl_sig = -1;

void	print_ast(t_ast *ast)
{
	if (ast)
		printf("%s\n", ast->value);
	if (ast->left)
		print_ast(ast->left);
	if (ast->right)
		print_ast(ast->right);
}

int	main(int ac, char *argv[])
{
	char		*line;
	t_parser	*parser;
	t_ast		*ast;

	suppress_output();
	while (1)
	{
		signal_handler();
		rl_catch_signals = 0;
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