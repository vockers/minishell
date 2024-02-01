/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:42:20 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:42:20 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include <stdbool.h>

#include "libft.h"

int	run_echo(char **args)
{
	bool	newline;

	newline = true;
	if (*(++args) != NULL)
	{
		while (*args && ft_strncmp(*args, "-n", 2) == 0 && (*args)[2] != '-')
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
