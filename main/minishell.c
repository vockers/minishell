#include "minishell.h"

int	mini_init(t_mini *ms, char **envp)
{
	ms->env = env_init(envp);
	ms->envp = env_to_strs(ms->env);
	if (ms->envp == NULL)
		return (0);
	return (1);
}

void	mini_cleanup(t_mini *ms)
{
	env_free(ms->env);
	free(ms->envp);
}
