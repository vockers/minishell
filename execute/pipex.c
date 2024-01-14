#include "execute.h"

void	here_doc_dup(t_ast *ast, t_list **fds)
{
	t_list	*temp;
	int		*fd_hdoc;

	fd_hdoc = (int *)temp->content;
	if (ast && ast->type == AST_HEREDOC)
	{
		dup2(*fd_hdoc, STDIN_FILENO);
		close(*fd_hdoc);
	}
}

static void	child_process_left(t_ast *ast, int *fds, int infd, t_list **fd_hdoc)
{
	close(fds[0]);
	if (infd != STDIN_FILENO)
	{
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	infile_handler(ast->right);
	here_doc_dup(ast, fd_hdoc);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	execute(ast);
}

static void	child_process_right(t_ast *ast, int *fds, t_list **fd_hdoc)
{
	close(fds[1]);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	if (ast->type == AST_ARG)
	{
		outfile_handler(ast->right);
		if (here_doc_handler(ast->right, 1) == 2)
			exit(EXIT_SUCCESS);
		execute(ast);
	}
	else if (ast->type == AST_PIPE)
	{
		pipex(ast, fds[0]);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
	}
}

t_list	**get_fd_hdoc(t_ast *ast, t_list **fds)
{
	t_list	*new;
	int		fd_new;

	if (ast && ast->type == AST_HEREDOC)
	{
		fd_new = here_doc_handler(ast, 1);
		if (!ft_lstnew(&fd_new) || fd_new == -1)
		{
			ft_lstclear(fds, free);
			return (NULL);
		}
		ft_lstadd_back(fds, new);
	}
	if (ast && ast->left)
		get_fd_hdoc(ast->left, fds);
	if (ast && ast->right)
		get_fd_hdoc(ast->right, fds);
	return (fds);
}

void	pipex(t_ast *ast, int infd)
{
	int		fds[2];
	pid_t	pid[2];
	t_list	*fd_hdoc;

	fd_hdoc = NULL;
	if (!get_fd_hdoc(ast, &fd_hdoc))
		exit(EXIT_FAILURE);
	if (gl_sig == SIGINT)
		exit(130);
	display_error(pipe(fds), "pipe");
	pid[0] = fork();
	display_error(pid[0], "fork");
	if (pid[0] == 0)
		child_process_left(ast->left, fds, infd, &fd_hdoc);
	pid[1] = fork();
	display_error(pid[1], "fork");
	if (pid[1] == 0)
		child_process_right(ast->right, fds, &fd_hdoc);
	close(fds[0]);
	close(fds[1]);
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], NULL, 0);
}
