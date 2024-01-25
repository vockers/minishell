/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:42:02 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:42:02 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include <linux/limits.h>

#include "libft.h"

int	run_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
