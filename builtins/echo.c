#include "builtins.h"

#include <stdbool.h>

#include "libft.h"

int	run_echo(char **args)
{
	bool	newline;

	newline = true;
	if (*(++args) != NULL)
	{
		while (*args && ft_strcmp(*args, "-n") == 0)
		{
			newline = false;
			args++;
		}
		while (*args)
		{
			ft_putstr_fd(*args++, STDOUT_FILENO);
			if (*args)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
