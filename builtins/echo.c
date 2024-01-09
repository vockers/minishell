#include "builtins.h"

#include <stdbool.h>

#include "libft.h"

int	builtin_echo(char **args)
{
	bool	newline;

	newline = true;
	if (*args == NULL)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		return (0);
	}
	while (*args && (*args)[0] == '-')
	{
		if ((*args)[1] == 'n' && (*args)[2] == '\0')
			newline = false;
		else
		{
			printf("%s", *args++);
			break;
		}
		args++;
	}
	while (*args)
	{
		printf("%s", *args);
		args++;
		if (*args)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}