#include "builtins.h"

#include "libft.h"

int	run_unset(char **args, t_env *env)
{
	if (!args[1])
		return (EXIT_SUCCESS);
	env_remove(env, args[1]);
	free(env->strs);
	env->strs = env_to_strs(env->head);
	return (EXIT_SUCCESS);
}
