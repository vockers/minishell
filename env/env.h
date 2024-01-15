#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*env_init(char **envp);
void	env_free(t_env *env);
void	env_append(t_env **env, char *value);
char	**env_to_strs(t_env *env);

#endif