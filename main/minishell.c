/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:22:08 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:22:08 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_init(t_mini *ms, int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: %s: too many arguments\n", \
			argv[1]);
		return (0);
	}
	if (!env_init(&(ms->env), envp))
		return (0);
	ms->exit = false;
	ms->status = 0;
	return (1);
}

void	mini_cleanup(t_mini *ms)
{
	env_free(ms->env.head);
	free(ms->env.strs);
}
