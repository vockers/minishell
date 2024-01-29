/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:21:16 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:21:16 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "ast.h"
# include "env.h"

typedef struct s_parser
{
	t_token	next_token;
	t_ast	*ast;
	t_env	*env;
}	t_parser;

void	parser_parse(t_parser *parser, char *line, int status, t_env *env);
t_token	parser_eat(t_parser *parser, enum e_token token_type);
void	parser_cleanup(t_parser *parser);

t_ast	*parse_command(t_parser *parser, int status, t_env *env);

char	*expand_argument(char *str, int status, t_env *env);

#endif
