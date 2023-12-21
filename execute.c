/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:30:14 by jcaro             #+#    #+#             */
/*   Updated: 2023/12/21 16:16:55 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "libft/libft.h"

char	*free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	*error_msg(char *cmd)
{
	size_t	len;
	char	*msg;

	len = ft_strlen("zsh: command not found: \n");
	len += ft_strlen(cmd);
	msg = (char *)malloc(len + 1);
	if (!msg)
		return (NULL);
	ft_strlcpy(msg, "zsh: command not found: ", len + 1);
	ft_strlcat(msg, cmd, len + 1);
	ft_strlcat(msg, "\n", len + 1);
	return (msg);
}

void	execute(char **argv, char **envp)
{
	char	**args;
	char	*cmd_path;
	char	*msg;

	cmd_path = pathname(argv[0], envp);
	if (execve(cmd_path, argv, envp) == -1)
	{
		msg = error_msg(argv[0]);
		if (!msg)
			perror("zsh");
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
