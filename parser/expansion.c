/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:21:43 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:21:43 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	get_name_len(char *str)
{
	char	*begin;

	begin = str;
	while (*str && *str != '$' && !lexer_is_delimiter(*str) && \
		*str != '\'' && *str != '"')
		str++;
	return (str - begin);
}

static char	*expand_env(char *str, size_t *i, t_env *env)
{
	char	*name;
	char	*value;
	char	*new_str;
	size_t	name_len;
	size_t	new_len;

	name_len = get_name_len(str + *i);
	if (name_len == 0)
		return (str);
	name = ft_strndup(str + *i, name_len);
	value = get_env_value(env, name);
	free(name);
	new_len = ft_strlen(str) - name_len + ft_strlen(value);
	new_str = ft_calloc(new_len + 1, sizeof(char));
	if (new_str == NULL)
		return (free(str), NULL);
	ft_strlcpy(new_str, str, *i);
	if (value != NULL)
		ft_strlcat(new_str, value, new_len);
	ft_strlcat(new_str, str + *i + name_len, new_len);
	free(str);
	*i += ft_strlen(value) - 1;
	return (new_str);
}

static char	*expand_status(char *str, size_t i, int status)
{
	char	*arg;
	char	*new_str;
	size_t	new_len;

	arg = ft_itoa(status);
	if (arg == NULL)
		return (free(str), NULL);
	new_len = ft_strlen(str) - 1 + ft_strlen(arg);
	new_str = (char *)ft_calloc(new_len, sizeof(char));
	if (new_str == NULL)
		return (free(arg), free(str), NULL);
	ft_strlcpy(new_str, str, i);
	ft_strlcat(new_str, arg, new_len);
	ft_strlcat(new_str, str + i + 1, new_len);
	free(str);
	free(arg);
	return (new_str);
}

static char	*expand_var(char *str, size_t *i, int status, t_env *env)
{
	if (str[*i] == '?')
		return (expand_status(str, *i, status));
	return (expand_env(str, i, env));
}

char	*expand_argument(char *str, int status, t_env *env)
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
			str = expand_var(str, &i, status, env);
	}
	return (str);
}
