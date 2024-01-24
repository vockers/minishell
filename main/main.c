#include "minishell.h"

#include "execute.h"

int	gl_sig = -1;

int	main(int ac, char *argv[], char **envp)
{
	t_mini		ms;
	t_parser	parser;
	char		*line;

	if (!mini_init(&ms, envp))
		return (1);
	suppress_output();
	parser.status = 0;
	parser.env = &(ms.env);
	while (!ms.exit)
	{
		signal_handler();
		rl_catch_signals = 0;
		line = readline("msh> ");
		if (!line)
			return (mini_cleanup(&ms), 0);
		if (ft_strcmp(line, "") == 0)
		{
			free(line);
			continue;
		}
		parser_parse(&parser, line);
		parser.status = exe_line(parser.ast, &ms);
		ast_destroy(parser.ast);
		free(line);
	}
	mini_cleanup(&ms);
	return (0);
}
