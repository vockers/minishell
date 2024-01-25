#include "execute.h"

static void	no_cmdx_pipe(t_ast *ast, t_mini *ms, t_list *hdoc_fd)
{
	infile_handler(ast);
	outfile_handler(ast);
	redirec_heredoc(ast, hdoc_fd);
	exit(EXIT_SUCCESS);
}

static void	child_process_left(t_ast *ast, int *fds, t_list *hdoc_fd, t_mini *ms)
{
	close(fds[0]);
	if (redirec_heredoc(ast->right, hdoc_fd))
	{
		if (fds[3] != STDIN_FILENO)
			close(fds[3]);
	}
	else if (fds[3] != STDIN_FILENO)
	{
		dup2(fds[3], STDIN_FILENO);
		close(fds[3]);
	}
	if (ast->type == AST_ARG)
	{
		infile_handler(ast->right);
		dup2(fds[1], STDOUT_FILENO);
		close(fds[1]);
		outfile_handler(ast->right);
		if (is_builtin(ast->value))
			exit(builtin_exec(ast, ms));
		else
			execute(ast, ms);
	}
	else
		no_cmdx_pipe(ast, ms, hdoc_fd);
}

static void	child_process_right(t_ast *ast, int *fds, t_list *hdoc_fd, t_mini *ms)
{
	close(fds[1]);
	if (!redirec_heredoc(ast->right, hdoc_fd))
	{
		dup2(fds[0], STDIN_FILENO);
		close(fds[0]);
	}
	if (ast->type == AST_ARG)
	{
		infile_handler(ast->right);
		outfile_handler(ast->right);
		if (is_builtin(ast->value))
			exit(builtin_exec(ast, ms));
		else
			execute(ast, ms);
	}
	else if (ast->type == AST_PIPE)
	{
		pipex(ast, fds[0], hdoc_fd, ms);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
	else
		no_cmdx_pipe(ast, ms, hdoc_fd);
}

int	pipex(t_ast *ast, int infd, t_list *hdoc_fd, t_mini *ms)
{
	int		fds[3];
	pid_t	pid[2];
	int		status[2];

	fds[2] = infd;
	display_error(pipe(fds), "pipe");
	pid[0] = fork();
	display_error(pid[0], "fork");
	if (pid[0] == 0)
		child_process_left(ast->left, fds, hdoc_fd, ms);
	pid[1] = fork();
	display_error(pid[1], "fork");
	if (pid[1] == 0)
		child_process_right(ast->right, fds, hdoc_fd, ms);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	exit_handler(status[0]);
	return (exit_handler(status[1]));
}
