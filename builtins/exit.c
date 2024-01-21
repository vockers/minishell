#include "builtins.h"

#include "../libft/libft.h"

int	run_exit(char **args)
{
	ft_putstr_fd("exit", STDERR_FILENO);
	if (args[1] && !ft_strisnum(args[1]))
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: "
			"%s: numeric argument required\n", args[1]);
		return (2);
	}
	else if (args[1] && args[2])
	{
		ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		return (1);
	}
	else if (args[1])
		return (ft_atoi(args[1]));
	return (EXIT_SUCCESS);
}
