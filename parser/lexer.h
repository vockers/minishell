#ifndef LEXER_H
# define LEXER_H

# include "libft.h"

# define TOKEN_COUNT 6

enum e_token
{
	T_NONE,
	T_ARG,
	T_PIPE,
	T_GRT,
	T_LSR,
	T_D_GRT,
	T_D_LSR
};

typedef struct s_token
{
	enum e_token	type;
	char			*str;
}	t_token;

typedef struct s_match_spec
{
	char 			*(*func)(char *);
	enum e_token	type;
}	t_match_spec;

t_token	get_next_token(char *line);

bool lexer_is_redirect(enum e_token type);

#endif