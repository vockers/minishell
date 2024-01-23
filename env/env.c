#include "env.h"

#include "libft.h"

t_env	*env_init(char **envp)
{
	t_env	*head;

	head = NULL;
	while (*envp)
	{
		env_append(&head, *envp);
		envp++;
	}
	return (head);
}

void	env_free(t_env *env)
{
	if (env == NULL)
		return ;
	if (env->next)
		env_free(env->next);
	free(env->value);
	free(env);
}

void	env_append(t_env **env, char *value)
{
	t_env	*last;
	t_env	*new;

	if (env == NULL)
		return ;
	new = (t_env *)ft_calloc(1, sizeof(t_env));
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

void	env_update(t_env **env, char *value)
{
	t_env	*iter;
	size_t	value_len;

	if (env == NULL)
		return ;
	iter = *env;
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
	env_append(env, value);
}

void	env_remove(t_env **env, char *value)
{
	t_env	*iter;
	t_env	*prev;
	size_t	value_len;

	if (env == NULL)
		return ;
	iter = *env;
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
				*env = iter->next;
			free(iter->value);
			return (free(iter));
		}
		prev = iter;
		iter = iter->next;
	}
}
