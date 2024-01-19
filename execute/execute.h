#ifndef EXECUTE_H

# define EXECUTE_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include "../signals/signals.h"

# include "../parser/parser.h"

void	exe_line(t_ast *ast);
void	exit_handler(int status);
void	pipex(t_ast *ast, int infd, t_list *hdoc_fd);
void	display_error(int fd, char *error);
char	*pathname(char *cmd);
void	execute(t_ast *ast);
char	*free_arr(char **arr);
char	**free_arr_i(char **arr, int i);
void	outfile_error(char *file);
void	infile_error(char *file);
void	outfile_handler(t_ast *ast);
int		infile_handler(t_ast *ast);
void	here_doc_handler(t_ast *ast);
int		read_loop(char *delimiter, int fd, char *msg);
int		heredoc_pipe_read(t_ast *ast, t_list **hdoc_fd, int i);
int		redirec_heredoc(t_ast *ast, t_list *hdoc_fd);
t_list	**add_fd(t_list **fds, char *file_name);
char	*create_file_name(int i);
void	delete_files(t_list **hdoc_fd);

#endif