/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:42:26 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:42:26 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"
# include "../main/minishell.h"

int	run_cd(char **args, t_env *env);
int	run_echo(char **args);
int	run_env(char **envp);
int	run_exit(char **args, t_mini *ms);
int	run_export(t_env *env, char **args);
int	run_pwd(void);
int	run_unset(char **args, t_env *env);

#endif
