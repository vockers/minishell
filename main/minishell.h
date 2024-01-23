#ifndef MINISHELL_H
# define MINISHELL_H

# include "builtins.h"
# include "env.h"
# include "execute.h"
# include "parser.h"
# include "signals.h"

typedef struct s_mini
{
	t_env		*env;
	char		**envp;
	bool		exit;
}	t_mini;

int		mini_init(t_mini *ms, char **envp);
void	mini_cleanup(t_mini *ms);

#endif
