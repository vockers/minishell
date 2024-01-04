#include "execute.h"

void	child_process_left(t_ast *ast, char **envp, int *fds, int infd)
{
	int	fd_infile;

	close(fds[0]);
	dup2(infd, STDIN_FILENO);
	close(infd);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	execute(ast->value, envp);
}

void	child_process_right(t_ast *ast, char **envp, int *fds)
{
	int	fd_outfile;

	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	if (ast->type == 1)
	{
		outfile_handler(ast->right);
		execute(ast->value, envp);
	}
	else if (ast->type == 0)
		pipex(ast, envp, fds[0]);
}

void	pipex(t_ast *ast, char **envp, int infd)
{
	int		fds[2];
	pid_t	pid[2];

	display_error(pipe(fds), "pipe");
	pid[0] = fork();
	display_error(pid[0], "fork");
	if (pid[0] == 0)
		child_process_left(ast->left, envp, fds, infd);
	pid[1] = fork();
	display_error(pid[1], "fork");
	if (pid[1] == 0)
		child_process_right(ast->right, envp, fds);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
