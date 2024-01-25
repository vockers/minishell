#include "parser.h"

static char	*expand_env(char *str, size_t i, t_env *env)
{
	char	*name;
	char	*value;
	char	*new_str;
	size_t	name_len;
	size_t	new_len;

	name_len = i;
	while (str[name_len] && !lexer_is_delimiter(str[name_len]) && \
		str[name_len] != '\'' && str[name_len] != '"')
		name_len++;
	name_len = name_len - i;
	name = ft_strndup(str + i, name_len);
	value = get_env_value(env, name);
	free(name);
	new_len = ft_strlen(str) - name_len + ft_strlen(value);
	new_str = ft_calloc(new_len + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str, i);
	if (value != NULL)
		ft_strlcat(new_str, value, new_len);
	ft_strlcat(new_str, str + i + name_len, new_len);
	free(str);
	return (new_str);
}

static char	*expand_status(char *str, size_t i, int status)
{
	char	*arg;
	char	*new_str;
	size_t	new_len;

	arg = ft_itoa(status);
	if (arg == NULL)
		return (str);
	new_len = ft_strlen(str) - 1 + ft_strlen(arg);
	new_str = (char *)ft_calloc(new_len, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str, i);
	ft_strlcat(new_str, arg, new_len);
	ft_strlcat(new_str, str + i + 1, new_len);
	free(str);
	free(arg);
	return (new_str);
}

static char	*expand_var(char *str, size_t i, t_parser *parser)
{
	if (str[i] == '?')
		return (expand_status(str, i, parser->status));
	return (expand_env(str, i, parser->env));
}

char	*expand_argument(char *str, t_parser *parser)
{
	bool	inside_quote;
	bool	inside_dquote;
	size_t	i;

	inside_quote = false;
	inside_dquote = false;
	i = 0;
	while (str && str[i])
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
		else if (str[i++] == '$' && !inside_quote)
			str = expand_var(str, i, parser);
	}
	return (str);
}
