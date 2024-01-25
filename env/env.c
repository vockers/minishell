/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:32:43 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:32:43 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

#include "libft.h"

int	env_init(t_env *env, char **envp)
{
	size_t	i;

	env->head = NULL;
	env->strs = NULL;
	i = 0;
	while (envp[i])
	{
		env_append(&(env->head), envp[i]);
		i++;
	}
	if (env_len(env) != i)
		return (0);
	if (!env_to_strs(env))
		env_free(env->head);
	return (1);
}

void	env_free(t_envlst *env)
{
	if (env == NULL)
		return ;
	if (env->next)
		env_free(env->next);
	free(env->value);
	free(env);
}

void	env_append(t_envlst **env, char *value)
{
	t_envlst	*last;
	t_envlst	*new;

	if (env == NULL)
		return ;
	new = (t_envlst *)ft_calloc(1, sizeof(t_envlst));
	if (new == NULL)
		return ;
	new->value = ft_strdup(value);
	if (*env)
	{
		last = *env;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		*env = new;
}

void	env_update(t_env *env, char *value)
{
	t_envlst	*iter;
	size_t		value_len;

	if (env == NULL)
		return ;
	iter = env->head;
	while (iter)
	{
		value_len = 0;
		while (iter->value[value_len] && iter->value[value_len] != '=')
			value_len++;
		if (ft_strncmp(iter->value, value, value_len) == 0)
		{
			if (value[value_len] == '=')
			{
				free(iter->value);
				iter->value = ft_strdup(value);
			}
			return ;
		}
		iter = iter->next;
	}
	env_append(&(env->head), value);
	env_to_strs(env);
}

void	env_remove(t_env *env, char *value)
{
	t_envlst	*iter;
	t_envlst	*prev;
	size_t		value_len;

	if (env == NULL)
		return ;
	iter = env->head;
	prev = NULL;
	while (iter)
	{
		value_len = 0;
		while (iter->value[value_len] && iter->value[value_len] != '=')
			value_len++;
		if (ft_strncmp(iter->value, value, value_len) == 0)
		{
			if (prev != NULL)
				prev->next = iter->next;
			else
				env->head = iter->next;
			free(iter->value);
			return (free(iter));
		}
		prev = iter;
		iter = iter->next;
	}
}
