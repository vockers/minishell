#include "parser.h"

#include <stdlib.h>

#include "libft.h"

static t_token	parser_eat(t_parser *parser, enum e_token token_type)
{
	t_token	current_token;

	current_token = parser->next_token;
	if (current_token.type == T_NONE)
	{
		ft_printf("Unexpected end of input, expected: %d\n", token_type);
		exit(1);
	}
	if (current_token.type != token_type)
	{
		ft_printf("Unexpected token, expected: %d\n", token_type);
		exit(1);
	}
	parser->next_token = get_next_token(NULL);
	return (current_token);
}

/**
 * Arguments
 *	: ARG
 *	| ARG Arguments
 * 	;
*/
static t_ast	*parse_arguments(t_parser *parser)
{
	t_ast	*node;
	t_token	token;

	node = ast_new(AST_ARG);
	if (node == NULL)
		return (NULL);
	token = parser_eat(parser, T_ARG);
	token.str = expand_argument(token.str);
	node->value = token.str;
	if (parser->next_token.type == T_ARG)
		node->left = parse_arguments(parser);
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
	token = parser_eat(parser, T_ARG);
	node->left = ast_new(AST_ARG);
	if (node->left == NULL)
		return (NULL);
	node->left->value = token.str;
	if (token_is_redirect(parser->next_token.type))
		node->right = parse_redirect(parser);
	return (node);
}

/**
 * Command
 * 	: Arguments
 * 	| Arguments Redirect
 * 	| Redirect Arguments
 * 	| Redirect Arguments Redirect
 * 	;
*/
static t_ast	*parse_command(t_parser *parser)
{
	t_ast	*node;
	t_ast	*redirect_node;

	redirect_node = NULL;
	if (token_is_redirect(parser->next_token.type))
		redirect_node = parse_redirect(parser);
	node = parse_arguments(parser);
	node->right = redirect_node;
	if (token_is_redirect(parser->next_token.type))
	{
		redirect_node = node;
		while (redirect_node->right)
			redirect_node = redirect_node->right;
		redirect_node->right = parse_redirect(parser);
	}
	return (node);
}

/**
 * Pipe
 * 	: Command
 * 	| Command '|' Pipe
 * 	;
*/
static t_ast	*parse_pipe(t_parser *parser)
{
	t_ast	*ret;
	t_ast	*node;
	t_token	token;

	ret = parse_command(parser);
	if (parser->next_token.type == T_PIPE)
	{
		node = ret;
		ret = ast_new(AST_PIPE);
		ret->left = node;
		token = parser_eat(parser, T_PIPE);
		ret->value = token.str;
		ret->right = parse_pipe(parser);
	}
	return (ret);
}

t_parser	*parser_init(char *line)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (parser == NULL)
		return (NULL);
	parser->next_token = get_next_token(line);
	return (parser);
}

t_ast	*parser_parse(t_parser *parser)
{
	return (parse_pipe(parser));
}
