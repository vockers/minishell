#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>

#include "libft.h"

static bool	is_valid_env(const char *env)
{
	if (ft_isdigit(*env) || *env == '=')
		return (false);
	env++;
	while (*env && *env != '=')
	{
		if (!ft_isalnum(*env))
			return (false);
		env++;
	}
	return (true);
}

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
	size_t	j;

	env_len = 0;
	while (envp[env_len])
		env_len++;
	sorted_env = (char **)ft_calloc(env_len + 1, sizeof(char *));
	if (sorted_env == NULL)
		return ;
	i = 0;
	while (*envp)
		sorted_env[i++] = *envp++;
	sorted_env = sort_envp(sorted_env);
	i = 0;
	while (i < env_len)
	{
		ft_printf("export ");
		j = 0;
		while (sorted_env[i][j])
		{
			ft_putchar_fd(sorted_env[i][j], STDOUT_FILENO);
			if (sorted_env[i][j++] == '=')
				ft_putchar_fd('"', STDOUT_FILENO);
		}
		ft_printf("\"\n");
		i++;
	}
	free(sorted_env);
}

int	run_export(char ***envp, char **args)
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
	return (EXIT_SUCCESS);
}
