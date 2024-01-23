#include "builtins.h"

#include <linux/limits.h>
#include <errno.h>
#include <string.h>

#include "libft.h"

static void	update_oldpwd(t_env *env)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (old_pwd == NULL)
		return ;
	env_update(env, old_pwd);
	free(old_pwd);
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
	update_oldpwd(env);
	return (chdir(path));
}

int	run_cd(char **args, t_env *env)
{
	int	ret;

	if (!args[1])
		return (go_to_env(env, "HOME"));
	if (ft_strcmp(args[1], "-") == 0)
		return (go_to_env(env, "OLDPWD"));
	update_oldpwd(env);
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
	return (ret);
}
