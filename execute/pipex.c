#include "execute.h"

static void	child_process_left(t_ast *ast, int *fds, int infd, t_list *hdoc_fd)
{
	close(fds[0]);
	if (redirec_heredoc(ast->right, hdoc_fd))
	{
		if (infd != STDIN_FILENO)
			close(infd);
	}
	else if (infd != STDIN_FILENO)
	{
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	infile_handler(ast->right);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	execute(ast);
}

static void	child_process_right(t_ast *ast, int *fds, t_list *hdoc_fd)
{
	close(fds[1]);
	if (!redirec_heredoc(ast->right, hdoc_fd))
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (ast->type == AST_ARG)
	{
		outfile_handler(ast->right);
		execute(ast);
	}
	else if (ast->type == AST_PIPE)
	{
		pipex(ast, fds[0], hdoc_fd);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
}

void	pipex(t_ast *ast, int infd, t_list *hdoc_fd)
{
	int		fds[2];
	pid_t	pid[2];
	int		status[2];

	display_error(pipe(fds), "pipe");
	pid[0] = fork();
	display_error(pid[0], "fork");
	if (pid[0] == 0)
		child_process_left(ast->left, fds, infd, hdoc_fd);
	pid[1] = fork();
	display_error(pid[1], "fork");
	if (pid[1] == 0)
		child_process_right(ast->right, fds, hdoc_fd);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	exit_handler(status[0]);
	exit_handler(status[1]);
}
