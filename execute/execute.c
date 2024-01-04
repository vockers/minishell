#include "execute.h"

char	*error_msg(char *cmd)
{
	size_t	len;
	char	*msg;

	len = ft_strlen("minishell: command not found: \n");
	len += ft_strlen(cmd);
	msg = (char *)malloc(len + 1);
	if (!msg)
		return (NULL);
	ft_strlcpy(msg, "minishell: command not found: ", len + 1);
	ft_strlcat(msg, cmd, len + 1);
	ft_strlcat(msg, "\n", len + 1);
	return (msg);
}

void	execute(char *cmd, char **envp)
{
	char	**args;
	char	*cmd_path;
	char	*msg;

	args = ft_split(cmd, ' ');
	if (!args)
		exit(EXIT_FAILURE);
	cmd_path = pathname(args[0], envp);
	if (execve(cmd_path, args, envp) == -1)
	{
		msg = error_msg(cmd);
		if (msg)
		{
			ft_putstr_fd(msg, STDERR_FILENO);
			free(msg);
		}
		free_arr(args);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
}
