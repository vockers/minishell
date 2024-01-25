/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:42:16 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:42:16 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
