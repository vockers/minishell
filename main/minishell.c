#include "minishell.h"

int	mini_init(t_mini *ms, char **envp)
{
	env_init(&(ms->env), envp);
	ms->exit = false;
	return (1);
}

void	mini_cleanup(t_mini *ms)
{
	env_free(ms->env.head);
	free(ms->env.strs);
}
