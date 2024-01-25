/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:42:12 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:42:12 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include "libft.h"

int	run_exit(char **args, t_mini *ms)
{
	ms->exit = true;
	ft_putendl_fd("exit", STDERR_FILENO);
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
