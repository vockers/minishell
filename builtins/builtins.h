#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"

int	run_cd(char **args, t_env *env);
int	run_echo(char **args);
int	run_env(char **envp);
int	run_exit(char **args);
int	run_export(t_env *env, char **args);
int	run_pwd(void);
int	run_unset(char **args, t_env *env);

#endif