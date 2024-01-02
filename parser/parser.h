#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

enum e_ast
{
	AST_PIPE,
	AST_ARG,
	AST_GRT,
	AST_LSR,
	AST_APPEND,
	AST_HEREDOC
};

typedef struct s_ast
{
	enum e_ast		type;
	char			*value;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_parser
{
	t_token	next_token;
}	t_parser;

t_parser	*parser_init(char *line);
t_ast		*parser_parse(t_parser *parser);

t_ast		*ast_new(enum e_ast type);
void 		ast_destroy(t_ast *ast);

#endif