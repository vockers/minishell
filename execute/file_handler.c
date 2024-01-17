#include "execute.h"

void	outfile_handler(t_ast *ast)
{
	int	fd_outfile;

	if (ast && (ast->type == AST_GRT || ast->type == AST_APPEND))
	{
		fd_outfile = -1;
		outfile_error(ast->left->value);
		if (ast->type == AST_GRT)
			fd_outfile = open(ast->left->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ast->type == AST_APPEND)
			fd_outfile = open(ast->left->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_outfile == -1)
			exit(EXIT_FAILURE);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd_outfile);
	}
	else if (ast)
		outfile_handler(ast->right);
}

int	infile_handler(t_ast *ast)
{
	int	fd_infile;

	if (ast && ast->type == AST_LSR)
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

int	read_loop(char *delimiter, int fd, char *msg)
{
	int		status;
	char	*line;

	status = 1;
	rl_catch_signals = 0;
	line = readline(msg);
	while (line && ft_strcmp(line, delimiter))
	{
		if (gl_sig != -1)
		{
			status = 0;
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(msg);
	}
	if (line)
		free(line);
	close (fd);
	return (status);
}

static int	write_temp_file(char *delimiter)
{
	int		fd;

	if (!delimiter)
	{
		printf("msh: parse error near `\\n'\n");
		return (-1);
	}
	fd = open("tmp_file", O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	read_loop(delimiter, fd, "heredoc> ");
	return (fd);
}

void	here_doc_handler(t_ast *ast)
{
	int		fd;

	if (ast && ast->type == AST_HEREDOC)
	{
		signal_handler_heredoc();
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
