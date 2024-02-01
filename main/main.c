/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcaro <jcaro@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:22:12 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/29 13:55:07 by jcaro         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute.h"

int	g_sig = -1;

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
	parser_cleanup(&(ms->parser));
	free(line);
}

int	main(int argc, char *argv[], char **envp)
{
	t_mini	ms;
	char	*line;

	argc = 0;
	argv = NULL;
	if (!mini_init(&ms, envp))
		return (1);
	suppress_output();
	while (!ms.exit)
	{
		signal_handler();
		line = readline("msh> ");
		if (!line)
		{
			ms.status = 0;
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		status_signal(&ms);
		process_line(line, &ms);
	}
	mini_cleanup(&ms);
	return (ms.status);
}
