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
