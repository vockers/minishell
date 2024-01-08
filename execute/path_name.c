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

char	*pathname(char *cmd)
{
	char	**path_list;
	char	*pathname;

	path_list = get_path_list(getenv("PATH"));
	if (!path_list)
		return (NULL);
	pathname = get_pathname(path_list, cmd);
	return (pathname);
}
