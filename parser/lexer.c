#include "lexer.h"

#include <stdbool.h>

static char	*expand_arg(char *str)
{
	bool	inside_quote;
	bool	inside_dquote;
	size_t	i;

	inside_quote = false;
	inside_dquote = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !inside_dquote)
		{
			inside_quote = !inside_quote;
			ft_strcpy(str + i, str + i + 1);
		}
		else if (str[i] == '"' && !inside_quote)
		{
			inside_dquote = !inside_dquote;
			ft_strcpy(str + i, str + i + 1);
		}
		else
		{
			// if (str[i] == '$')
			// 
			i++;
		}
	}
	return (str);
}

static t_token	scan_arg(char *str)
{
	bool	inside_quote;
	bool	inside_dquote;
	size_t	i;

	inside_quote = false;
	inside_dquote = false;
	i = 0;
	while (str[i] && \
		(!lexer_is_delimiter(str[i]) || inside_quote || inside_dquote))
	{
		if (str[i] == '\'' && !inside_dquote)
			inside_quote = !inside_quote;
		else if (str[i] == '"' && !inside_quote)
			inside_dquote = !inside_dquote;
		i++;
	}
	return ((t_token){T_ARG, ft_strndup(str, i)});
}

static t_token	scan_token(char *str)
{
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
	return (scan_arg(str));
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
	token = scan_token(saved);
	saved += ft_strlen(token.str);
	if (token.type == T_ARG)
		token.str = expand_arg(token.str);
	return (token);
}
