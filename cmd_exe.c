/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:04:56 by jcaro             #+#    #+#             */
/*   Updated: 2023/12/21 16:34:29 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft/libft.h"

void	display_error(int fd, char *error)
{
	if (fd == -1)
	{
		perror(error);
		exit(EXIT_FAILURE);
	}
}

void	cmd_exe(char **argv, char **envp)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	display_error(pipe(fd), "pipe");
	pid = fork();
	display_error(pid, "fork");
	if (pid == 0)
		execute(argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	exit(status);
}

int	main(int ac, char *argv[], char **envp)
{
	if (ac == 1)
		return (0);
	else
		cmd_exe(argv + 1, envp);
	return (0);
}
