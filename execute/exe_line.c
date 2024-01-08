#include "execute.h"

void	single_cmdx(t_ast *ast)
{
	int		fd[2];
	pid_t	pid;

	display_error(pipe(fd), "pipe");
	pid = fork();
	display_error(pid, "fork");
	if (pid == 0)
	{
		infile_handler(ast->right);
		outfile_handler(ast->right);
		here_doc_handler(ast->right, 0);
		execute(ast);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
}

void	exe_line(t_ast *ast, int infd)
{
	if (ast->type == AST_PIPE)
		pipex(ast, infd);
	else if (ast->type == AST_ARG)
	{
		single_cmdx(ast);
	}
}