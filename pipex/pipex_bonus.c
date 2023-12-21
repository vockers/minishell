/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:59:13 by jcaro             #+#    #+#             */
/*   Updated: 2023/12/21 18:46:44 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../libft/libft.h"

int	wait_for_children(int cmd_count, pid_t *pid)
{
	int	i;
	int	status;
	int	final;

	i = 0;
	final = 0;
	while (i < cmd_count)
	{
		waitpid(pid[i], &status, 0);
		if (status != 0)
			final = status;
		i++;
	}
	return (final);
}

pid_t	*create_pid(int cmd_count, int **fds)
{
	pid_t	*pid;

	pid = (pid_t *)malloc(cmd_count);
	if (!pid)
	{
		free_arr_bonus(fds, cmd_count);
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	pipex_bonus(int cmd_count, char **argv, char **envp)
{
	int		**fds;
	pid_t	*pid;
	int		i;
	int		status;

	fds = create_pipes(cmd_count - 1);
	if (!fds)
		exit(EXIT_FAILURE);
	pid = create_pid(cmd_count, fds);
	i = 0;
	while (i < cmd_count)
	{
		pid[i] = fork();
		display_error(pid[i], "fork");
		if (pid[i] == 0)
			exec_child_process(argv, envp, fds, i);
		i++;
	}
	close_all(fds, cmd_count - 1);
	status = wait_for_children(cmd_count, pid);
	free_arr_bonus(fds, cmd_count);
	free(pid);
	exit(status);
}
