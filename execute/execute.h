/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:10:26 by jcaro             #+#    #+#             */
/*   Updated: 2024/01/29 15:35:17 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H

# define EXECUTE_H

# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include "../signals/signals.h"

# include "../main/minishell.h"

# include "../parser/parser.h"

int		exe_line(t_ast *ast, t_mini *ms);
int		exit_handler(int status);
int		pipex(t_ast *ast, int infd, t_list *hdoc_fd, t_mini *ms);
void	display_error(int fd, char *error);
char	*pathname(char *cmd);
char	**get_args(t_ast *ast);
void	execute(t_ast *ast, t_mini *ms);
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
int		is_builtin(char *cmd);
int		builtin_exec(t_ast *ast, t_mini *ms);

#endif
