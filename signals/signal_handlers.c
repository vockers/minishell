/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:11:36 by jcaro             #+#    #+#             */
/*   Updated: 2024/01/26 15:08:55 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static void	sigint_handler(int signum)
{
	g_sig = signum;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler(t_mini *ms)
{
	rl_catch_signals = 0;
	status_signal(ms);
	signal_handler_init(&sigint_handler, SIGINT);
	signal_handler_init(&ft_empty, SIGQUIT);
}

void	signal_handler_child(void)
{
	signal_handler_init(&ft_empty, SIGINT);
	signal_handler_init(&ft_empty, SIGQUIT);
}

static void	sigint_heredoc(int signum)
{
	g_sig = signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}

void	signal_handler_heredoc(void)
{
	signal_handler_init(&sigint_heredoc, SIGINT);
	signal_handler_init(&ft_empty, SIGQUIT);
}
