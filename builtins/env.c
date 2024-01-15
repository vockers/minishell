#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>

int	run_env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		envp++;
	}
	return (EXIT_SUCCESS);
}
