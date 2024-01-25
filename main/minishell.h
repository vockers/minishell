#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>

# include "env.h"

typedef struct s_mini
{
	t_env	env;
	bool	exit;
}	t_mini;

int		mini_init(t_mini *ms, char **envp);
void	mini_cleanup(t_mini *ms);

#endif
