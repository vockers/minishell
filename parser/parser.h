#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "ast.h"

typedef struct s_parser
{
	t_token	next_token;
	t_ast	*ast;
	int		status;
}	t_parser;

void	parser_parse(t_parser *parser);
char	*expand_argument(char *str, int status);

#endif
