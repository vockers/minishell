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
	int		status;
}	t_parser;

void	parser_parse(t_parser *parser, char *line);
t_token	parser_eat(t_parser *parser, enum e_token token_type);

t_ast	*parse_command(t_parser *parser);

char	*expand_argument(char *str, t_parser *parser);

#endif
