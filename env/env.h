#ifndef ENV_H
# define ENV_H

# include <stdbool.h>

typedef struct s_envlst
{
	char			*value;
	struct s_envlst	*next;
}	t_envlst;

typedef struct s_env
{
	char		**strs;
	t_envlst	*head;
}	t_env;

void	env_init(t_env *env, char **envp);
void	env_free(t_envlst *env);
void	env_append(t_envlst **env, char *value);
void	env_update(t_env *env, char *value);
void	env_remove(t_env *env, char *value);
char	*get_env_value(t_env *env, char *name);
char	**env_to_strs(t_envlst *env);

bool	is_valid_env(const char *env);

#endif
