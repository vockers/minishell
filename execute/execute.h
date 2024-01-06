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
void	execute(t_ast *ast, char **envp);
char	*free_arr(char **arr);
char	**free_arr_i(char **arr, int i);
void	outfile_error(char *file);
void	infile_error(char *file);
void	outfile_handler(t_ast *ast);
int		infile_handler(t_ast *ast);
void	here_doc_handler(t_ast *ast);

#endif