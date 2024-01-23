#include <stdio.h>
#include <stdlib.h>

#include "builtins/builtins.h"
#include "env.h"

int	main(int argc, char *argv[], char **envp)
{
	t_env	*env;
	t_env	*iter;

	env_init(&env, envp);
	env_to_strs(env);
	run_env(env->strs);
	free(env->strs);
	env_free(env->head);
	return (0);
}
