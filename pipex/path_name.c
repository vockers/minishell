/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:23:31 by jcaro             #+#    #+#             */
/*   Updated: 2023/12/21 18:33:30 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../libft/libft.h"

char	*get_paths(char **envp)
{
	char	*paths;
	char	**env_vars;
	int		i;
	int		len;

	i = 0;
	paths = NULL;
	while (envp[i] != NULL)
	{
		env_vars = ft_split(envp[i], '=');
		if (!env_vars)
			return (NULL);
		len = ft_strlen(env_vars[0]);
		if (len == 4 && ft_strncmp("PATH", env_vars[0], 4) == 0)
		{
			paths = ft_strdup(env_vars[1]);
			break ;
			if (!paths)
				return (free_arr(env_vars));
		}
		free_arr(env_vars);
		i++;
	}
	return (paths);
}

char	**get_path_list(char *paths)
{
	char	**path_list;

	if (!paths)
		return (NULL);
	path_list = ft_split(paths, ':');
	free(paths);
	if (!path_list)
		return (NULL);
	return (path_list);
}

char	*get_pathname(char **path_list, char *cmd)
{
	int		i;
	char	*pathname;
	char	*path_fix;

	i = 0;
	while (path_list[i])
	{
		path_fix = ft_strjoin(path_list[i], "/");
		if (!path_fix)
			return (free_arr(path_list));
		pathname = ft_strjoin(path_fix, cmd);
		free(path_fix);
		if (!pathname)
			return (free_arr(path_list));
		if (access(pathname, F_OK | X_OK) == 0)
		{
			free_arr(path_list);
			return (pathname);
		}
		free(pathname);
		i++;
	}
	return (free_arr(path_list));
}

char	*pathname(char *cmd, char **envp)
{
	char	**path_list;
	char	*pathname;

	path_list = get_path_list(get_paths(envp));
	if (!path_list)
		return (NULL);
	pathname = get_pathname(path_list, cmd);
	return (pathname);
}
