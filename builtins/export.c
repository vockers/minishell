#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"

static char	**sort_envp(char **envp)
{
	char	*tmp;
	size_t	i;
	size_t	j;
	size_t	min_idx;

	i = 0;
	while (envp[i])
	{
		min_idx = i;
		j = i + 1;
		while (envp[j])
		{
			if (ft_strcmp(envp[j], envp[min_idx]) < 0)
				min_idx = j;
			j++;
		}
		tmp = envp[i];
		envp[i] = envp[min_idx];
		envp[min_idx] = tmp;
		i++;
	}
	return (envp);
}

static void	print_sorted_env(char **envp)
{
	char	**sorted_env;
	size_t	env_len;
	size_t	i;

	env_len = 0;
	while (envp[env_len])
		env_len++;
	sorted_env = (char **)ft_calloc(env_len + 1, sizeof(char *));
	if (sorted_env == NULL)
		return ;
	i = 0;
	while (envp[i])
	{
		sorted_env[i] = envp[i];
		i++;
	}
	sorted_env = sort_envp(sorted_env);
	i = 0;
	while (i < env_len)
		printf("export %s\n", sorted_env[i++]);
	free(sorted_env);
}

int	run_export(char **envp, char **args)
{
	if (!args[1])
	{
		print_sorted_env(envp);
		return (EXIT_SUCCESS);
	}
}
