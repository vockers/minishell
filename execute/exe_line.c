#include "execute.h"

void	exit_handler(int status)
{
	if (status == 2 || status == 131)
		write(STDOUT_FILENO, "\n", 1);
}

void	single_cmdx(t_ast *ast)
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
		execute(ast);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, &status, 0);
	exit_handler(status);
}

void	exe_line(t_ast *ast)
{
	t_list	*hdoc_fd;

	signal_handler_child();
	if (ast->type == AST_PIPE)
	{
		hdoc_fd = NULL;
		if (!heredoc_pipe_read(ast, &hdoc_fd, 0))
		{
			gl_sig = -1;
			return ;
		}
		pipex(ast, STDIN_FILENO, hdoc_fd);
		ft_lstclear(&hdoc_fd, free);
	}
	else if (ast->type == AST_ARG)
	{
		single_cmdx(ast);
	}
}
