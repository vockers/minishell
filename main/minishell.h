/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:22:05 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:22:05 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>

# include "env.h"
# include "parser.h"

typedef struct s_mini
{
	t_env		env;
	bool		exit;
	t_parser	parser;
	int			status;
}	t_mini;

int		mini_init(t_mini *ms, char **envp);
void	mini_cleanup(t_mini *ms);

#endif
