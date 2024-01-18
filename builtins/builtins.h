#ifndef BUILTINS_H
# define BUILTINS_H

# include "env.h"

int	run_echo(char **args);
int	run_pwd(void);
int	run_export(t_env **env, char ***envp, char **args);
int	run_env(char **envp);

#endif