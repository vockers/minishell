/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:11:49 by jcaro             #+#    #+#             */
/*   Updated: 2024/02/03 14:30:19 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H

# define SIGNALS_H

# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include "minishell.h"

extern int	g_sig;

void	signal_handler(void);
void	signal_handler_child(void);
void	signal_handler_heredoc(void);
void	suppress_output(void);
void	signal_handler_init(void (*f)(int), int sig_type);
void	ft_empty(int signum);
void	status_signal(t_mini *ms);

#endif