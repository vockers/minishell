#include <stdio.h>

#include "env.h"

int	main(int argc, char *argv[], char **envp)
{
	t_env	*env;
	t_env	*iter;

	env = env_init(envp);
	iter = env;
	while (iter)
	{
		printf("%s\n", iter->value);
		iter = iter->next;
	}
	env_free(env);
	return (0);
}
