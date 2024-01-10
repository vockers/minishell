#include "builtins.h"

#include <stdio.h>
#include <stdlib.h>

int	builtins_echo(char **envp)
{
	while (*envp)
	{
		printf("%s", *envp);
		envp++;
	}
	return (EXIT_SUCCESS);
}
