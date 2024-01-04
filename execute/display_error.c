#include "execute.h"

void	display_error(int fd, char *error)
{
	if (fd == -1)
	{
		perror(error);
		exit(EXIT_FAILURE);
	}
}

char	*create_msg(char *error, char *file)
{
	size_t	len;
	char	*msg;
	char	c[2];

	len = ft_strlen("minishell: : \n");
	len += ft_strlen(error) + ft_strlen(file);
	msg = (char *)malloc(len + 1);
	if (!msg)
		return (NULL);
	ft_strlcpy(msg, "minishell: ", len + 1);
	c[0] = ft_tolower(error[0]);
	c[1] = '\0';
	ft_strlcat(msg, c, len + 1);
	ft_strlcat(msg, error + 1, len + 1);
	ft_strlcat(msg, ": ", len + 1);
	ft_strlcat(msg, file, len + 1);
	ft_strlcat(msg, "\n", len + 1);
	return (msg);
}

void	outfile_error(char *file)
{
	char	*msg;

	if (access(file, F_OK) == -1)
		return ;
	if (access(file, W_OK) == -1)
	{
		msg = create_msg(strerror(errno), file);
		if (msg)
		{
			ft_putstr_fd(msg, STDERR_FILENO);
			free(msg);
		}
		exit(EXIT_FAILURE);
	}
}

void	infile_error(char *file)
{
	char	*msg;

	if (access(file, R_OK) == -1)
	{
		msg = create_msg(strerror(errno), file);
		if (msg)
		{
			ft_putstr_fd(msg, STDERR_FILENO);
			free(msg);
		}
		exit(EXIT_FAILURE);
	}
}
