#ifndef EXECUTE_H

# define EXECUTE_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>

# include "../parser/parser.h"

void	exe_line(t_ast *ast, char **envp, int infd);
void	pipex(t_ast *ast, char **envp, int infd);
void	display_error(int fd, char *error);
char	*pathname(char *cmd, char **envp);
void	execute(char *cmd, char **envp);
char	*free_arr(char **arr);
void	outfile_error(char *file);
void	outfile_handler(t_ast *ast);

#endif