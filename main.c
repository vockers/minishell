/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliacaro <juliacaro@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:04:05 by juliacaro         #+#    #+#             */
/*   Updated: 2023/12/30 15:11:39 by juliacaro        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft/libft.h"

int	main(int ac, char *argv[], char **envp)
{
	t_list	*here_doc_input;

	if (ac == 1)
		return (0);
	else if (ft_strcmp(argv[1], "<<") == 0)
	{
		here_doc_input = here_doc_handler(argv[2]);
		ft_lstclear(&here_doc_input, free);
	}
	else
		cmd_exe(argv + 1, envp);
	// if (ac < 5)
	// 	exit(EXIT_FAILURE);
	// pipex_bonus(ac - 3, argv, envp);
	return (0);
}
