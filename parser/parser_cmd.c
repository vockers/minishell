/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_cmd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:21:27 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:21:27 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stdlib.h>

#include "libft.h"

/**
 * Arguments
 *	: ARG
 *	| ARG Arguments
 * 	;
*/
static t_ast	*parse_arguments(t_parser *parser, int status, t_env *env)
{
	t_ast	*node;
	t_token	token;

	token = parser_eat(parser, T_ARG);
	if (token.type == T_NONE)
		return (NULL);
	node = ast_new(AST_ARG);
	if (node == NULL)
		return (NULL);
	token.str = expand_argument(token.str, status, env);
	if (token.str == NULL)
		return (ast_destroy(node), NULL);
	node->value = token.str;
	if (parser->next_token.type == T_ARG)
	{
		node->left = parse_arguments(parser, status, env);
		if (node->left == NULL)
			return (ast_destroy(node), NULL);
	}
	return (node);
}

/**
 * RedirectOperator
 * 	: '>'
 * 	| '<'
 * 	| '>>'
 * 	| '<<'
 * 	;
*/
static t_ast	*parse_redirect_operator(t_parser *parser)
{
	t_ast	*node;
	t_token	token;

	token = parser_eat(parser, parser->next_token.type);
	if (token.type == T_NONE)
		return (NULL);
	if (token.type == T_GRT)
		node = ast_new(AST_GRT);
	else if (token.type == T_LSR)
		node = ast_new(AST_LSR);
	else if (token.type == T_D_GRT)
		node = ast_new(AST_APPEND);
	else
		node = ast_new(AST_HEREDOC);
	if (node == NULL)
		return (NULL);
	node->value = token.str;
	return (node);
}

/**
 * Redirect
 * 	: RedirectOperator ARG
 * 	| RedirectOperator ARG Redirect
 * 	;
 *
*/
static t_ast	*parse_redirect(t_parser *parser)
{
	t_ast	*node;
	t_token	token;

	node = parse_redirect_operator(parser);
	if (node == NULL)
		return (NULL);
	token = parser_eat(parser, T_ARG);
	if (token.type == T_NONE)
		return (ast_destroy(node), NULL);
	node->left = ast_new(AST_ARG);
	if (node->left == NULL)
		return (NULL);
	node->left->value = token.str;
	if (token_is_redirect(parser->next_token.type))
	{
		node->right = parse_redirect(parser);
		if (node->right == NULL)
			return (ast_destroy(node), NULL);
	}
	return (node);
}

int	parse_red_args(t_parser *parser, t_ast *parent_node, int status, t_env *env)
{
	t_ast	*last_node;

	last_node = parent_node;
	while (last_node->right != NULL)
		last_node = last_node->right;
	last_node->right = parse_redirect(parser);
	if (last_node->right == NULL)
		return (0);
	if (parser->next_token.type == T_ARG)
	{
		last_node = parent_node;
		while (last_node->left != NULL)
			last_node = last_node->left;
		last_node->left = parse_arguments(parser, status, env);
		if (last_node->left == NULL)
			return (0);
	}
	return (1);
}

/**
 * Command
 * 	: Arguments
 * 	| Redirect
 * 	| Arguments Redirect
 * 	| Redirect Arguments
 * 	| Redirect Arguments Redirect
 * 	;
*/
t_ast	*parse_command(t_parser *parser, int status, t_env *env)
{
	t_ast	*node;
	t_ast	*redirect_node;

	redirect_node = NULL;
	if (token_is_redirect(parser->next_token.type))
	{
		redirect_node = parse_redirect(parser);
		if (redirect_node == NULL || \
			(parser->next_token.type != T_ARG))
			return (redirect_node);
	}
	node = parse_arguments(parser, status, env);
	if (node == NULL)
		return (ast_destroy(redirect_node), NULL);
	node->right = redirect_node;
	while (token_is_redirect(parser->next_token.type))
	{
		if (!parse_red_args(parser, node, status, env))
			return (ast_destroy(node), NULL);
	}
	return (node);
}
