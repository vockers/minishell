#include "execute.h"

void	outfile_handler(t_ast *ast)
{
	int	fd_outfile;

	if (ast && ast->type == 2)
	{
		outfile_error(ast->left->value);
		fd_outfile = open(ast->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_outfile == -1)
			exit(EXIT_FAILURE);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
}
