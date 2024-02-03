/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:17:27 by jcaro             #+#    #+#             */
/*   Updated: 2024/02/03 14:38:30 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	exit_handler(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (status == 2 && g_sig == SIGINT)
	{
		g_sig = -1;
		return (130);
	}
	else if (status == 131)
		return (status);
	else
		return (status);
}

int	exit_handler_signal(int status)
{
	if (status == SIGINT || status == 130)
		write(STDOUT_FILENO, "\n", 1);
	else if (status == 131)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	return (status);
}

void	exit_handler_pipe(int status, int infd)
{
	if (infd == STDIN_FILENO && g_sig == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
	else if (infd == STDIN_FILENO && g_sig == SIGQUIT)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	if (infd == STDIN_FILENO && WIFEXITED(status))
		g_sig = -1;
}
