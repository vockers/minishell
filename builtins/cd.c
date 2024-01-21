#include "builtins.h"

#include <linux/limits.h>

#include "libft.h"

static void	update_oldpwd(t_env **env, char ***envp)
{
	char	cwd[PATH_MAX];
	char	*old_pwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return ;
	old_pwd = ft_strjoin("OLDPWD=", cwd);
	if (old_pwd == NULL)
		return ;
	env_update(env, old_pwd);
	free(*envp);
	*envp = env_to_strs(*env);
}

static int	go_home(t_env **env, char ***envp)
{
	char	*home_path;

	update_oldpwd(env, envp);
	home_path = getenv("HOME");
	if (home_path == NULL)
	{
		ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (1);
	}
	return (chdir(home_path));
}

int	run_cd(char **args, t_env **env, char ***envp)
{
	if (!args[1])
		return (go_home(env, envp));
}