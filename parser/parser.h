#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"
# include "ast.h"

typedef struct s_parser
{
	t_token	next_token;
	t_ast	*ast;
}	t_parser;

t_parser	*parser_init(char *line);
void		parser_parse(t_parser *parser);

char		*expand_argument(char *str);

#endif
