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

int	mini_init(t_mini *ms, char **envp)
{
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
