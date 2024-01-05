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

int	infile_handler(t_ast *ast)
{
	int	fd_infile;

	if (ast && ast->type == 3)
	{
		infile_error(ast->left->value);
		fd_infile = open(ast->left->value, O_RDONLY, 0644);
		if (fd_infile == -1)
			exit(EXIT_FAILURE);
		dup2(fd_infile, STDIN_FILENO);
		close(fd_infile);
		return (1);
	}
	return (0);
}

int	write_temp_file(char *delimiter)
{
	char	*line;
	int		fd;

	if (!delimiter)
	{
		printf("ms: parse error near `\\n'\n");
		return (-1);
	}
	fd = open("tmp_file", O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	line = readline("heredoc> ");
	while (ft_strcmp(line, delimiter))
	{
		write(fd, line, ft_strlen(line) + 1);
		line = readline("heredoc> ");
	}
	close(fd);
	return (fd);
}

void	here_doc_handler(t_ast *ast)
{
	int		fd;

	if (ast && ast->type == 5)
	{
		fd = write_temp_file(ast->left->value);
		if (fd == -1)
			return ;
		fd = open("tmp_file", O_RDONLY);
		if (fd != -1)
		{
			unlink("tmp_file");
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
}
