/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:32:50 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:32:50 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

#include "libft.h"

size_t	env_len(t_env *env)
{
	t_envlst	*iter;
	size_t		i;

	if (env == NULL)
		return (0);
	iter = env->head;
	i = 0;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	return (i);
}

bool	is_valid_env(const char *env)
{
	if (ft_isdigit(*env) || *env == '=')
		return (false);
	env++;
	while (*env && *env != '=')
	{
		if (!ft_isalnum(*env))
			return (false);
		env++;
	}
	return (true);
}

char	*get_env_value(t_env *env, char *name)
{
	t_envlst	*iter;
	size_t		value_len;

	if (env == NULL || name == NULL)
		return (NULL);
	iter = env->head;
	while (iter)
	{
		value_len = 0;
		while (iter->value[value_len] && iter->value[value_len] != '=')
			value_len++;
		if (ft_strncmp(iter->value, name, value_len) == 0)
		{
			if (iter->value[value_len] == '=')
				return (iter->value + value_len + 1);
		}
		iter = iter->next;
	}
	return (NULL);
}

int	env_to_strs(t_env *env)
{
	t_envlst	*iter;
	size_t		i;
	char		**new;

	if (env == NULL)
		return (0);
	new = (char **)ft_calloc(env_len(env) + 1, sizeof(char *));
	if (new == NULL)
		return (0);
	iter = env->head;
	i = 0;
	while (iter)
	{
		new[i++] = iter->value;
		iter = iter->next;
	}
	free(env->strs);
	env->strs = new;
	return (1);
}
