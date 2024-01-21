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

char	**env_to_strs(t_env *env)
{
	t_env	*iter;
	size_t	i;
	char	**new;

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
