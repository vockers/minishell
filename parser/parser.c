/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:21:24 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:21:24 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stdlib.h>

#include "libft.h"

t_token	parser_eat(t_parser *parser, enum e_token token_type)
{
	t_token	current_token;

	current_token = parser->next_token;
	if (current_token.type == T_NONE)
	{
		ft_dprintf(STDERR_FILENO, "minishell: unexpected end of input\n");
		return (current_token);
	}
	if (current_token.type != token_type)
	{
		ft_dprintf(STDERR_FILENO, \
			"minishell: syntax error near unexpected token `%s'\n", \
			current_token.str);
		return ((t_token){T_NONE, NULL});
	}
	parser->next_token = get_next_token(NULL);
	return (current_token);
}

/**
 * Pipe
 * 	: Command
 * 	| Command '|' Pipe
 * 	;
*/
static t_ast	*parse_pipe(t_parser *parser, int status, t_env *env)
{
	t_ast	*ret;
	t_ast	*node;
	t_token	token;

	ret = parse_command(parser, status, env);
	if (ret == NULL)
		return (NULL);
	if (parser->next_token.type == T_PIPE)
	{
		node = ret;
		ret = ast_new(AST_PIPE);
		if (ret == NULL)
			return (ast_destroy(node), NULL);
		ret->left = node;
		token = parser_eat(parser, T_PIPE);
		ret->value = token.str;
		ret->right = parse_pipe(parser, status, env);
		if (ret->right == NULL)
			return (ast_destroy(ret), NULL);
	}
	return (ret);
}

void	parser_parse(t_parser *parser, char *line, int status, t_env *env)
{
	parser->next_token = get_next_token(line);
	parser->ast = parse_pipe(parser, status, env);
}

void	parser_cleanup(t_parser *parser)
{
	free(parser->next_token.str);
	ast_destroy(parser->ast);
}
