#include "env.h"

#include "libft.h"

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

char	**env_to_strs(t_envlst *env)
{
	t_envlst	*iter;
	size_t		i;
	char		**new;

	if (env == NULL)
		return (NULL);
	iter = env;
	i = 0;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	new = (char **)ft_calloc(i + 1, sizeof(char *));
	if (new == NULL)
		return (NULL);
	iter = env;
	i = 0;
	while (iter)
	{
		new[i++] = iter->value;
		iter = iter->next;
	}
	return (new);
}
