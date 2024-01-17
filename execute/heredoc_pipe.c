#include "execute.h"

static t_list	**add_fd(t_list **fds, char *file_name)
{
	t_list	*new;

	if (!file_name)
		return (NULL);
	new = ft_lstnew(file_name);
	if (!new)
	{
		ft_lstclear(fds, free);
		return (NULL);
	}
	ft_lstadd_back(fds, new);
	return (fds);
}

static char	*create_file_name(int i)
{
	char	*name;

	name = (char *)malloc(sizeof(char) * 14);
	if (!name)
		return (NULL);
	ft_strlcpy(name, "tmp_file_", 14);
	ft_strlcat(name, ft_itoa(i), 14);
	return (name);
}

static char	*write_temp_file(char *delimiter, int i)
{
	char	*line;
	int		fd;
	char	*name;

	if (!delimiter)
	{
		printf("msh: parse error near `\\n'\n");
		return (NULL);
	}
	name = create_file_name(i);
	if (!name)
		return (NULL);
	fd = open(name, O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
	if (fd == -1)
	{
		free(name);
		return (NULL);
	}
	line = readline("pipe heredoc> ");
	read_loop(line, delimiter, fd, "pipe heredoc> ");
	return (name);
}

void	heredoc_pipe_read(t_ast *ast, t_list **hdoc_fd, int i)
{
	int		fd;
	char	*file_name;

	if (ast && ast->type == AST_HEREDOC)
	{
		file_name = write_temp_file(ast->left->value, i);
		if (!add_fd(hdoc_fd, file_name))
			exit(EXIT_FAILURE);
	}
	if (ast->left)
		heredoc_pipe_read(ast->left, hdoc_fd, i);
	if (ast->right)
		heredoc_pipe_read(ast->right, hdoc_fd, i + 1);
}

int	redirec_heredoc(t_ast *ast, t_list *hdoc_fd)
{
	int		fd;

	if (ast && ast->type == AST_HEREDOC)
	{
		fd = open((char *)hdoc_fd->content, O_RDONLY);
		while (hdoc_fd && fd == -1)
		{
			hdoc_fd = hdoc_fd->next;
			fd = open((char *)hdoc_fd->content, O_RDONLY);
		}
		if (fd != -1)
		{
			unlink((char *)hdoc_fd->content);
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
			exit(EXIT_FAILURE);
		return (1);
	}
	return (0);
}
