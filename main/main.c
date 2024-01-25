#include "minishell.h"
#include "execute.h"

int	gl_sig = -1;

static void	process_line(char *line, t_mini *ms)
{
	if (ft_strcmp(line, "") == 0)
	{
		free(line);
		return ;
	}
	add_history(line);
	parser_parse(&(ms->parser), line, ms->status, &(ms->env));
	if (ms->parser.ast != NULL)
		ms->status = exe_line(ms->parser.ast, ms);
	else
		ms->status = 2;
	ast_destroy(ms->parser.ast);
	free(line);
}

int	main(int ac, char *argv[], char **envp)
{
	t_mini	ms;
	char	*line;

	if (!mini_init(&ms, envp))
		return (1);
	suppress_output();
	while (!ms.exit)
	{
		signal_handler();
		rl_catch_signals = 0;
		line = readline("msh> ");
		if (!line)
			break ;
		process_line(line, &ms);
	}
	mini_cleanup(&ms);
	return (ms.status);
}
