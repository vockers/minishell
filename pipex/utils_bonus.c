/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 18:45:11 by jcaro             #+#    #+#             */
/*   Updated: 2023/12/21 18:33:56 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../libft/libft.h"

int	*free_arr_bonus(int **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	arr_len(int	**arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	close_all(int **fds, int pipe_num)
{
	int	i;

	i = 0;
	while (i < pipe_num)
	{
		close(fds[i][0]);
		close(fds[i][1]);
		i++;
	}
}

void	close_except(int **fds, int n)
{
	int	i;

	i = 0;
	while (fds[i])
	{
		if (i != n && i != n - 1)
		{
			close(fds[i][0]);
			close(fds[i][1]);
		}
		i++;
	}
}

void	free_all(int **fds, int pipe_num, pid_t *pids)
{
	free_arr_bonus(fds, pipe_num + 1);
	free(pids);
}
