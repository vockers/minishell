#include "builtins.h"

#include "libft.h"

int	run_unset(char **args, t_env **env, char ***envp)
{
	if (!args[1])
		return (EXIT_SUCCESS);
	env_remove(env, args[1]);
	free(*envp);
	*envp = env_to_strs(*env);
	return (EXIT_SUCCESS);
}
