#include "minishell.h"

int	gl_sig = -1;

int	main(int ac, char *argv[], char **envp)
{
	t_mini		ms;
	t_parser	parser;
	char		*line;

	if (!mini_init(&ms, envp))
		return (1);
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
		parser.next_token = get_next_token(line);	
		parser_parse(&parser);
		ms.status = exe_line(parser.ast);
		ast_destroy(parser.ast);
		free(line);
	}
	mini_cleanup(&ms);
	return (0);
}
