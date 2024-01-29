/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:11:43 by jcaro             #+#    #+#             */
/*   Updated: 2024/01/29 15:18:51 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	suppress_output(void)
{
	struct termios	new_settings;

	if (tcgetattr(0, &new_settings))
		perror("tcsetattr");
	new_settings.c_lflag &= ~ECHOCTL;
	if (tcsetattr(0, 0, &new_settings))
		perror("tcsetattr");
}

void	signal_handler_init(void (*f)(int), int sig_type)
{
	struct sigaction	sa;

	sa.sa_handler = f;
	sa.sa_flags = SA_RESTART;
	if (sigaction(sig_type, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}
}

void	ft_empty(int signum)
{
	g_sig = signum;
}

void	status_signal(t_mini *ms)
{
	if (g_sig == SIGINT)
	{
		ms->status = 130;
		g_sig = -1;
	}
}

int	exit_handler_signal(int status)
{
	if (status == SIGINT || status == 130)
		write(STDOUT_FILENO, "\n", 1);
	else if (status == 131)
		write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	return (status);
}
