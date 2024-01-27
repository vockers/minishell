/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exe.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jcaro <jcaro@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 17:09:45 by jcaro         #+#    #+#                 */
/*   Updated: 2024/01/25 17:09:48 by jcaro         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

int	builtin_exec(t_ast *ast, t_mini *ms)
{
	int		status;
	char	**args;

	args = get_args(ast);
	if (!args)
		exit(EXIT_FAILURE);
	status = EXIT_SUCCESS;
	if (!ft_strcmp("echo", ast->value))
		status = run_echo(args);
	else if (!ft_strcmp("cd", ast->value))
		status = run_cd(args, &(ms->env));
	else if (!ft_strcmp("pwd", ast->value))
		status = run_pwd();
	else if (!ft_strcmp("export", ast->value))
		status = run_export(&(ms->env), args);
	else if (!ft_strcmp("unset", ast->value))
		status = run_unset(args, &(ms->env));
	else if (!ft_strcmp("env", ast->value))
		status = run_env(ms->env.strs);
	else if (!ft_strcmp("exit", ast->value))
		status = run_exit(args, ms);
	free(args);
	return (exit_handler(status));
}
