/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcaro <jcaro@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:42:12 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/30 12:41:00 by jcaro         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include "libft.h"

int	run_exit(char **args, t_mini *ms)
{
	ms->exit = true;
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putendl_fd("exit", STDERR_FILENO);
	if (args[1] && !ft_strisnum(args[1]))
	{
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			ft_dprintf(STDERR_FILENO, "minishell: exit: "
				"%s: numeric argument required\n", args[1]);
		else
			ft_dprintf(STDERR_FILENO, "minishell: exit: "
				"%s: numeric argument required", args[1]);
		return (2);
	}
	else if (args[1] && args[2])
	{
		ms->exit = false;
		if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
			ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments\n");
		else
			ft_dprintf(STDERR_FILENO, "minishell: exit: too many arguments");
		return (1);
	}
	else if (args[1])
		return (ft_atoi(args[1]));
	return (EXIT_SUCCESS);
}
