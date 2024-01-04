#include "lexer.h"

#include <stdbool.h>

static char	*match_arg(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
	{
		if (!ft_isalnum(str[i]))
			return (NULL);
		i++;
	}
	return (ft_strndup(str, i));
}

static char	*match_pipe(char *str)
{
	if (*str != '|')
		return (NULL);
	return (ft_strndup(str, 1));
}

static char	*match_greater(char *str)
{
	if (*str && *str == '>' && *(str + 1) != '>')
		return (ft_strndup(str, 1));
	return (NULL);
}

static char	*match_less(char *str)
{
	if (*str && *str == '<' && *(str + 1) != '<')
		return (ft_strndup(str, 1));
	return (NULL);
}

static char	*match_dgreater(char *str)
{
	if (*str && *str == '>' && *(str + 1) == '>')
		return (ft_strndup(str, 2));
	return (NULL);
}

static char	*match_dless(char *str)
{
	if (*str && *str == '<' && *(str + 1) == '<')
		return (ft_strndup(str, 2));
	return (NULL);
}

t_token	get_next_token(char *line)
{
	static char					*saved = NULL;
	int							i;
	char						*value;
	const static t_match_spec	specs[TOKEN_COUNT] = {
	{match_arg, T_ARG},
	{match_pipe, T_PIPE},
	{match_greater, T_GRT},
	{match_less, T_LSR},
	{match_dgreater, T_D_GRT},
	{match_dless, T_D_LSR},
	};

	if (line != NULL)
		saved = line;
	saved = lexer_skip_spaces(saved);
	if (*saved == '\0')
		return ((t_token){T_NONE, NULL});
	i = 0;
	while (i < TOKEN_COUNT)
	{
		value = (specs[i].func)(saved);
		if (value != NULL)
		{
			saved += ft_strlen(value);
			return ((t_token){specs[i].type, value});
		}
		i++;
	}
	return ((t_token){T_NONE, NULL});
}
