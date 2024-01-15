#include <stdio.h>
#include <stdlib.h>

#include "builtins.h"
#include "env.h"

int	main(int argc, char *argv[], char **envp)
{
	t_env	*env;
	t_env	*iter;
	char	**env_strs;

	env = env_init(envp);
	env_strs = env_to_strs(env);
	run_env(env_strs);
	free(env_strs);
	env_free(env);
	return (0);
}
