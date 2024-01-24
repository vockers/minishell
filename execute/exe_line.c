#include "execute.h"

int	exit_handler(int status)
{
	if (status == 2 || status == 131)
		write(STDOUT_FILENO, "\n", 1);
	if (status == 2 || status == 33280)
		return (130);
	else if (status == 32512)
		return (127);
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
		if (gl_sig == SIGINT)
			exit(130);
		execute(ast, ms);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
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
			gl_sig = -1;
			return (130);
		}
		status = pipex(ast, STDIN_FILENO, hdoc_fd, ms);
		ft_lstclear(&hdoc_fd, free);
		return (status);
	}
	else if (ast->type == AST_ARG)
	{
		if (is_builtin(ast->value))
			return (builtin_exec(ast, ms));
		else
			return (single_cmdx(ast, ms));
	}
	return (0);
}
