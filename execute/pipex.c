#include "execute.h"

static void	child_process_left(t_ast *ast, int *fds, int infd)
{
	close(fds[0]);
	if (infd != STDIN_FILENO)
	{
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	infile_handler(ast->right);
	if (here_doc_handler(ast->right, 1) == 2)
		exit(EXIT_SUCCESS);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	execute(ast);
}

static void	child_process_right(t_ast *ast, int *fds)
{
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	if (ast->type == AST_ARG)
	{
		outfile_handler(ast->right);
		execute(ast);
	}
	else if (ast->type == AST_PIPE)
		pipex(ast, fds[0]);
}

void	pipex(t_ast *ast, int infd)
{
	int		fds[2];
	pid_t	pid[2];

	display_error(pipe(fds), "pipe");
	pid[0] = fork();
	display_error(pid[0], "fork");
	if (pid[0] == 0)
		child_process_left(ast->left, fds, infd);
	pid[1] = fork();
	display_error(pid[1], "fork");
	if (pid[1] == 0)
		child_process_right(ast->right, fds);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
