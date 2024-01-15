#ifndef BUILTINS_H
# define BUILTINS_H

int	run_echo(char **args);
int	run_pwd(void);
int	run_export(char ***envp, char **args);
int	run_env(char **envp);

#endif