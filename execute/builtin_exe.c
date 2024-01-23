#include "execute.h"
#include "../builtins/builtins.h"

int	is_builtin(char *cmd)
{
	if (ft_strcmp("echo", cmd) == 0)
		return (1);
	else if (ft_strcmp("cd", cmd) == 0)
		return (1);
	else if (ft_strcmp("pwd", cmd) == 0)
		return (1);
	else if (ft_strcmp("export", cmd) == 0)
		return (1);
	else if (ft_strcmp("unset", cmd) == 0)
		return (1);
	else if (ft_strcmp("env", cmd) == 0)
		return (1);
	else if (ft_strcmp("exit", cmd) == 0)
		return (1);
	else
		return (0);
}

void	builtin_exec(t_ast *ast, int last)
{
	int		status;
	char	**args;

	args = get_args(ast);
	if (!args)
		exit(EXIT_FAILURE);
	status = EXIT_SUCCESS;
	if (!ft_strcmp("echo", ast->value))
		status = run_echo(args);
	else if (!ft_strcmp("pwd", ast->value))
		status = run_pwd();
	else if (last && !ft_strcmp("exit", ast->value))
		status = run_exit(args);
	free(args);
	exit(status);
}
