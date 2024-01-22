#include "execute.h"

void	exit_handler(int status)
{
	if (status == 130 || status == 131)
		write(STDOUT_FILENO, "\n", 1);
}

int	single_cmdx(t_ast *ast)
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
		if (is_builtin(ast->value))
			builtin_exec(ast, 1);
		else
			execute(ast);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	exit_handler(WEXITSTATUS(status));
	return (WEXITSTATUS(status));
}

int	exe_line(t_ast *ast)
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
		status = pipex(ast, STDIN_FILENO, hdoc_fd);
		ft_lstclear(&hdoc_fd, free);
		return (status);
	}
	else if (ast->type == AST_ARG)
	{
		return (single_cmdx(ast));
	}
	return (0);
}
