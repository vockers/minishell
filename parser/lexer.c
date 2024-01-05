#include "lexer.h"

#include <stdbool.h>

static t_token	match_token(char *str)
{
	size_t	i;

	if (*str == '|')
		return ((t_token){T_PIPE, ft_strndup(str, 1)});
	else if (*str == '>')
	{
		if (*(str + 1) == '>')
			return ((t_token){T_D_GRT, ft_strndup(str, 2)});
		return ((t_token){T_GRT, ft_strndup(str, 1)});
	}
	else if (*str == '<')
	{
		if (*(str + 1) == '<')
			return ((t_token){T_D_LSR, ft_strndup(str, 2)});
		return ((t_token){T_LSR, ft_strndup(str, 1)});
	}
	i = 0;
	while (!lexer_is_delimiter(str[i]))
		i++;
	return ((t_token){T_ARG, ft_strndup(str, i)});
}

t_token	get_next_token(char *line)
{
	t_token		token;
	char		*value;
	static char	*saved = NULL;

	if (line != NULL)
		saved = line;
	saved = lexer_skip_spaces(saved);
	if (*saved == '\0')
		return ((t_token){T_NONE, NULL});
	token = match_token(saved);
	saved += ft_strlen(token.str);
	return (token);
}
