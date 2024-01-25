/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:41:59 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:41:59 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

#include "libft.h"

int	run_unset(char **args, t_env *env)
{
	if (!args[1])
		return (EXIT_SUCCESS);
	env_remove(env, args[1]);
	env_to_strs(env);
	return (EXIT_SUCCESS);
}
