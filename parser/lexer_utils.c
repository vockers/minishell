#include "lexer.h"

bool	token_is_redirect(enum e_token type)
{
	return (type == T_GRT || \
			type == T_LSR || \
			type == T_D_GRT || \
			type == T_D_LSR);
}

char	*lexer_skip_spaces(char *line)
{
	while (ft_isspace(*line))
		line++;
	return (line);
}
