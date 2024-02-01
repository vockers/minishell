/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcaro <jcaro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 17:10:59 by jcaro             #+#    #+#             */
/*   Updated: 2024/02/01 18:34:26 by jcaro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static char	*write_temp_file(char *delimiter, int i)
{
	int		fd;
	char	*name;

	if (!delimiter)
	{
		printf("msh: parse error near `\\n'\n");
		return (NULL);
	}
	name = create_file_name(i);
	if (!name)
		return (NULL);
	fd = open(name, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd == -1)
	{
		free(name);
		return (NULL);
	}
	if (!read_loop(delimiter, fd, "pipe heredoc> "))
	{
		unlink(name);
		free(name);
		return (NULL);
	}
	return (name);
}

int	heredoc_pipe_read(t_ast *ast, t_list **hdoc_fd, int i)
{
	char	*file_name;
	int		status;

	status = 1;
	if (ast && ast->type == AST_HEREDOC)
	{
		signal_handler_heredoc();
		file_name = write_temp_file(ast->left->value, i);
		if (!add_fd(hdoc_fd, file_name))
		{
			delete_files(hdoc_fd);
			ft_lstclear(hdoc_fd, free);
			status = 0;
		}
	}
	if (ast->left && status)
		status = heredoc_pipe_read(ast->left, hdoc_fd, i);
	if (ast->right && status)
		status = heredoc_pipe_read(ast->right, hdoc_fd, i + 1);
	return (status);
}

int	redirec_heredoc(t_ast *ast, t_list *hdoc_fd)
{
	int		fd;

	if (ast && ast->type == AST_HEREDOC)
	{
		fd = open((char *)hdoc_fd->content, O_RDONLY);
		while (hdoc_fd && fd == -1)
		{
			hdoc_fd = hdoc_fd->next;
			fd = open((char *)hdoc_fd->content, O_RDONLY);
		}
		if (fd != -1)
		{
			unlink((char *)hdoc_fd->content);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
			exit(EXIT_FAILURE);
		return (1);
	}
	return (0);
}
