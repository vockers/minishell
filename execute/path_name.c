/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:11:10 by jcaro             #+#    #+#             */
/*   Updated: 2024/01/31 16:52:03 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	**get_path_list(char *paths)
{
	char	**path_list;

	if (!paths)
		return (NULL);
	path_list = ft_split(paths, ':');
	if (!path_list)
		return (NULL);
	return (path_list);
}

static char	*get_pathname(char **path_list, char *cmd)
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

char	*pathname(char *cmd, t_env *env)
{
	char	**path_list;
	char	*pathname;

	if (ft_strchr(cmd, '/') || cmd[0] == '.')
		return (cmd);
	path_list = get_path_list(get_env_value(env, "PATH"));
	if (!path_list)
		return (NULL);
	pathname = get_pathname(path_list, cmd);
	return (pathname);
}
