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

static void	print_env(char **envp)
{
	bool	in_quote;

	in_quote = false;
	while (*envp)
	{
		ft_printf("export ");
		while (**envp)
		{
			ft_putchar_fd(**envp, STDOUT_FILENO);
			if (**envp == '=')
			{
				ft_putchar_fd('"', STDOUT_FILENO);
				in_quote = true;
			}
			(*envp)++;
		}
		if (in_quote)
			ft_putchar_fd('"', STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		in_quote = false;
		envp++;
	}
}

static void	print_sorted_env(char **envp)
{
	char	**sorted_env;
	size_t	i;

	i = 0;
	while (envp[i])
		i++;
	sorted_env = (char **)ft_calloc(i + 1, sizeof(char *));
	if (sorted_env == NULL)
		return ;
	i = 0;
	while (*envp)
		sorted_env[i++] = *envp++;
	sorted_env = sort_envp(sorted_env);
	print_env(sorted_env);
	free(sorted_env);
}

int	run_export(t_env **env, char ***envp, char **args)
{
	if (!args[1])
	{
		print_sorted_env(*envp);
		return (EXIT_SUCCESS);
	}
	if (!is_valid_env(args[1]))
	{
		printf("minishell: export: '%s': not a valid identifier\n", args[1]);
		return (1);
	}
	env_append(env, args[1]);
	free(*envp);
	*envp = env_to_strs(*env);
	return (EXIT_SUCCESS);
}
