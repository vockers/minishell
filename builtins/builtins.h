#ifndef BUILTINS_H
# define BUILTINS_H

# include "../env/env.h"

int	run_echo(char **args);
int	run_env(char **envp);
int	run_exit(char **args);
int	run_export(t_env **env, char ***envp, char **args);
int	run_pwd(void);

#endif