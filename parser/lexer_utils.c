/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:21:40 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:21:40 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

bool	lexer_is_delimiter(char c)
{
	return (c == '|' || c == '<' || c == '>' || ft_isspace(c));
}
