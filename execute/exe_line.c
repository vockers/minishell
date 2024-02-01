/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exe_line.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcaro <jcaro@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 17:10:08 by jcaro         #+#    #+#                 */
/*   Updated: 2024/01/29 15:16:27 by jcaro         ########   odam.nl         */
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

int	single_cmdx(t_ast *ast, t_mini *ms)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	display_error(pipe(fd), "pipe");
	pid = fork();
	display_error(pid, "fork");
	if (pid == 0)
	{
		infile_handler(ast->right);
		outfile_handler(ast->right);
		here_doc_handler(ast->right);
		if (g_sig == SIGINT)
			exit(130);
		execute(ast, ms);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	exit_handler_signal(status);
	return (exit_handler(status));
}

static int	no_cmdx(t_ast *ast)
{
	int		fd[2];
	pid_t	pid;
	int		status;

	display_error(pipe(fd), "pipe");
	pid = fork();
	display_error(pid, "fork");
	if (pid == 0)
	{
		infile_handler(ast);
		outfile_handler(ast);
		here_doc_handler(ast);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	exit_handler_signal(status);
	return (exit_handler(status));
}

int	exe_line(t_ast *ast, t_mini *ms)
{
	t_list	*hdoc_fd;
	int		status;

	signal_handler_child();
	if (ast->type == AST_PIPE)
	{
		hdoc_fd = NULL;
		if (!heredoc_pipe_read(ast, &hdoc_fd, 0))
		{
			g_sig = -1;
			return (130);
		}
		status = pipex(ast, STDIN_FILENO, hdoc_fd, ms);
		ft_lstclear(&hdoc_fd, free);
		return (exit_handler_signal(status));
	}
	else if (ast->type == AST_ARG)
	{
		if (is_builtin(ast->value))
			return (builtin_exec(ast, ms));
		else
			return (single_cmdx(ast, ms));
	}
	else
		return (no_cmdx(ast));
}
