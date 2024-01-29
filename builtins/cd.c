/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:42:23 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:42:23 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include <linux/limits.h>
#include <errno.h>
#include <string.h>

#include "libft.h"

static void	update_pwdenv(t_env *env, char *name)
{
	char	cwd[PATH_MAX];
	char	*value;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	value = ft_strjoin(name, cwd);
	if (value == NULL)
		return ;
	env_update(env, value);
	free(value);
}

static int	go_to_env(t_env *env, char *name)
{
	char	*path;

	path = get_env_value(env, name);
	if (path == NULL)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s not set\n", name);
		return (1);
	}
	update_pwdenv(env, "OLDPWD=");
	return (chdir(path));
}

int	run_cd(char **args, t_env *env)
{
	int	ret;

	if (!args[1])
		return (go_to_env(env, "HOME"));
	if (ft_strcmp(args[1], "-") == 0)
		return (go_to_env(env, "OLDPWD"));
	update_pwdenv(env, "OLDPWD=");
	ret = chdir(args[1]);
	if (ret != 0)
	{
		ret *= -1;
		if (args[2])
			ft_dprintf(STDERR_FILENO, "minishell: cd: too many arguments\n");
		else
			ft_dprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", \
				strerror(errno), args[1]);
	}
	update_pwdenv(env, "PWD=");
	return (ret);
}
