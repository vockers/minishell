/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:10:19 by jcaro             #+#    #+#             */
/*   Updated: 2024/01/31 17:28:44 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

char	*error_msg(char *cmd)
{
	size_t	len;
	char	*msg;

	len = ft_strlen(": command not found\n");
	len += ft_strlen(cmd);
	msg = (char *)malloc(len + 1);
	if (!msg)
		return (NULL);
	ft_strlcpy(msg, cmd, len + 1);
	ft_strlcat(msg, ": command not found\n", len + 1);
	return (msg);
}

size_t	get_size_args(t_ast *ast)
{
	size_t	size;

	size = 0;
	while (ast)
	{
		ast = ast->left;
		size++;
	}
	return (size);
}

char	**get_args(t_ast *ast)
{
	char	**args;
	int		i;

	args = (char **)malloc((get_size_args(ast) + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (ast)
	{
		args[i] = (char *)malloc((ft_strlen(ast->value) + 1) * sizeof(char));
		if (!args[i])
			return (free_arr_i(args, i));
		args[i] = ft_strcpy(args[i], ast->value);
		i++;
		ast = ast->left;
	}
	args[i] = NULL;
	return (args);
}

static void	check_if_dir(char *path, char **args)
{
	struct stat	stats;
	size_t		len;
	char		*msg;

	stat(path, &stats);
	if (S_ISDIR(stats.st_mode))
	{
		len = ft_strlen("msh: ./signals: Is a directory\n");
		len += ft_strlen(path);
		msg = (char *)malloc(len + 1);
		if (!msg)
		{
			free_arr(args);
			exit(EXIT_FAILURE);
		}
		ft_strlcpy(msg, "msh: ", len + 1);
		ft_strlcat(msg, path, len + 1);
		ft_strlcat(msg, ": Is a directory\n", len + 1);
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
		free_arr(args);
		exit(126);
	}
}

void	execute(t_ast *ast, t_mini *ms)
{
	char	**args;
	char	*cmd_path;
	char	*msg;
	t_env	env;

	args = get_args(ast);
	if (!args)
		exit(EXIT_FAILURE);
	env = ms->env;
	cmd_path = pathname(args[0], &(ms->env));
	check_if_dir(cmd_path, args);
	if (execve(cmd_path, args, env.strs) == -1)
	{
		msg = error_msg(args[0]);
		if (msg)
		{
			ft_putstr_fd(msg, STDERR_FILENO);
			free(msg);
		}
		free_arr(args);
		exit(127);
	}
}
