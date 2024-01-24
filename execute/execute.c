#include "execute.h"

char	*error_msg(char *cmd)
{
	size_t	len;
	char	*msg;

	len = ft_strlen("msh: command not found: \n");
	len += ft_strlen(cmd);
	msg = (char *)malloc(len + 1);
	if (!msg)
		return (NULL);
	ft_strlcpy(msg, "msh: command not found: ", len + 1);
	ft_strlcat(msg, cmd, len + 1);
	ft_strlcat(msg, "\n", len + 1);
	return (msg);
}

size_t	get_size_args(t_ast *ast)
{
	size_t	size;

	size = 0;
	while (ast)
	{
		ast = ast->left;
		size++;
	}
	return (size);
}

char	**get_args(t_ast *ast)
{
	char	**args;
	int		i;

	args = (char **)malloc((get_size_args(ast) + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	i = 0;
	while (ast)
	{
		args[i] = (char *)malloc((ft_strlen(ast->value) + 1) * sizeof(char));
		if (!args[i])
			return (free_arr_i(args, i));
		args[i] = ft_strcpy(args[i], ast->value);
		i++;
		ast = ast->left;
	}
	args[i] = NULL;
	return (args);
}

void	execute(t_ast *ast, t_mini *ms)
{
	char	**args;
	char	*cmd_path;
	char	*msg;
	t_env	env;

	args = get_args(ast);
	if (!args)
		exit(EXIT_FAILURE);
	env = ms->env;
	cmd_path = pathname(args[0]);
	if (execve(cmd_path, args, env.strs) == -1)
	{
		msg = error_msg(args[0]);
		if (msg)
		{
			ft_putstr_fd(msg, STDERR_FILENO);
			free(msg);
		}
		free_arr(args);
		free(cmd_path);
		exit(127);
	}
}
