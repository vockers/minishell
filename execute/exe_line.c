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
		here_doc_handler(ast->right);
		infile_handler(ast->right, STDIN_FILENO);
		outfile_handler(ast->right, STDOUT_FILENO);
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
		infile_handler(ast, STDIN_FILENO);
		outfile_handler(ast, STDOUT_FILENO);
		here_doc_handler(ast);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	exit_handler_signal(status);
	return (exit_handler(status));
}

static int	pipe_exe(t_ast *ast, t_mini *ms)
{
	t_list	*hdoc_fd;
	int		status;

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

static int	single_cmdx_builtin(t_ast *ast, t_mini *ms)
{
	int	status;
	int	stdin_copy;
	int	stdout_copy;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	infile_handler(ast, STDIN_FILENO);
	outfile_handler(ast, STDOUT_FILENO);
	here_doc_handler(ast);
	status = builtin_exec(ast, ms);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	return (status);
}

int	exe_line(t_ast *ast, t_mini *ms)
{
	signal_handler_child();
	if (ast->type == AST_PIPE)
		return (pipe_exe(ast, ms));
	else if (ast->type == AST_ARG)
	{
		if (is_builtin(ast->value))
			return (single_cmdx_builtin(ast, ms));
		else
			return (single_cmdx(ast, ms));
	}
	else
		return (no_cmdx(ast));
}
