/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_pipes_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 19:15:05 by jcaro             #+#    #+#             */
/*   Updated: 2023/12/21 18:33:11 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"

int	**create_pipes(int pipe_count)
{
	int	**fds;
	int	i;

	fds = (pid_t **)malloc((pipe_count + 1) * sizeof(int *));
	if (!fds)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		fds[i] = (int *)malloc(2 * sizeof(int));
		if (!fds[i])
		{
			free_arr_bonus(fds, i);
			return (NULL);
		}
		display_error(pipe(fds[i]), "pipe");
		i++;
	}
	fds[i] = NULL;
	return (fds);
}
