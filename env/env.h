/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:32:47 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:32:47 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>
# include <stdlib.h>

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

int		env_init(t_env *env, char **envp);
void	env_free(t_envlst *env);
void	env_append(t_envlst **env, char *value);
void	env_update(t_env *env, char *value);
void	env_remove(t_env *env, char *value);

bool	is_valid_env(const char *env);
size_t	env_len(t_env *env);
char	*get_env_value(t_env *env, char *name);
int		env_to_strs(t_env *env);
size_t	env_name_len(char *name);

#endif
