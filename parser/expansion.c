#include "parser.h"

static char	*expand_env(char *str, size_t i)
{
	char	*name;
	char	*value;
	char	*new_str;
	size_t	name_len;
	size_t	new_len;

	name_len = i;
	while (str[name_len] && !lexer_is_delimiter(str[name_len]))
		name_len++;
	name_len = name_len - i;
	name = ft_strndup(str + i, name_len);
	value = getenv(name);
	if (value == NULL)
		return (str);
	new_len = ft_strlen(str) - name_len + ft_strlen(value) - 1;
	new_str = ft_calloc(new_len + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	ft_strlcpy(new_str, str, i);
	ft_strlcat(new_str, value, new_len);
	ft_strlcat(new_str, str + i + name_len, new_len);
	free(str);
	return (new_str);
}

char	*expand_argument(char *str)
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
			if (str[i] == '$')
				str = expand_env(str, i + 1);
			i++;
		}
	}
	return (str);
}
