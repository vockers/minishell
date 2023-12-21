/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:30:14 by jcaro             #+#    #+#             */
/*   Updated: 2023/12/21 18:50:07 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute.h"
#include "../libft/libft.h"

void	child_process(char **argv, char **envp)
{
	char	**args;
	char	*cmd_path;
	char	*msg;

	cmd_path = pathname(argv[0], envp);
	if (execve(cmd_path, argv, envp) == -1)
	{
		msg = error_msg(argv[0]);
		if (!msg)
			perror("minishell");
		else
		{
			ft_putstr_fd(msg, STDERR_FILENO);
			free(msg);
		}
		free_arr(args);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
}
