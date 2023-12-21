/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 20:13:48 by jcaro             #+#    #+#             */
/*   Updated: 2023/12/21 18:32:59 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../libft/libft.h"

void	child_process_infile(char **argv, char **envp, int **fds)
{
	int	fd_infile;

	close_except(fds, 0);
	close(fds[0][0]);
	infile_error(argv[1]);
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		exit(EXIT_FAILURE);
	dup2(fd_infile, STDIN_FILENO);
	close(fd_infile);
	dup2(fds[0][1], STDOUT_FILENO);
	close(fds[0][1]);
	execute(argv[2], envp);
}

void	child_process_middle(char **argv, char **envp, int **fds, int n)
{
	close_except(fds, n);
	close(fds[n - 1][1]);
	close(fds[n][0]);
	dup2(fds[n - 1][0], STDIN_FILENO);
	close(fds[n - 1][0]);
	dup2(fds[n][1], STDOUT_FILENO);
	close(fds[n][1]);
	execute(argv[n + 2], envp);
}

void	child_process_outfile(char **argv, char **envp, int **fds, int n)
{
	int	fd_outfile;

	close_except(fds, n);
	close(fds[n - 1][1]);
	dup2(fds[n - 1][0], STDIN_FILENO);
	close(fds[n - 1][0]);
	outfile_error(argv[n + 3]);
	fd_outfile = open(argv[n + 3], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		exit(EXIT_FAILURE);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);
	execute(argv[n + 2], envp);
}

void	exec_child_process(char **argv, char **envp, int **fds, int i)
{
	if (i == 0)
		child_process_infile(argv, envp, fds);
	else if (i == arr_len(fds))
		child_process_outfile(argv, envp, fds, i);
	else
		child_process_middle(argv, envp, fds, i);
}
