/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 20:17:27 by jcaro             #+#    #+#             */
/*   Updated: 2024/02/01 20:17:30 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	exit_handler(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (status == 2 && g_sig == SIGINT)
		return (130);
	else if (status == 131)
		return (status);
	else
		return (status);
}
