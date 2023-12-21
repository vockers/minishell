/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:23:40 by jcaro             #+#    #+#             */
/*   Updated: 2023/12/21 18:43:13 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H

# define EXECUTE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>

void	cmd_exe(char **argv, char **envp);
void	child_process(char **argv, char **envp);
char	*pathname(char *cmd, char **envp);
void	display_error(int fd, char *error);
void	outfile_error(char *file);
void	infile_error(char *file);
char	*free_arr(char **arr);
char	*pathname(char *cmd, char **envp);
void	execute(char *cmd, char **envp);
void	pipex_bonus(int cmd_count, char **argv, char **envp);
int		**create_pipes(int pipe_count);
int		*free_arr_bonus(int **arr, int size);
void	free_all(int **fds, int pipe_num, pid_t *pids);
int		arr_len(int	**arr);
void	exec_child_process(char **argv, char **envp, int **fds, int i);
void	close_all(int **fds, int pipe_num);
void	close_except(int **fds, int n);
char	*error_msg(char *cmd);

#endif