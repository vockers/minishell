/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:21:47 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:21:47 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

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

t_ast	*ast_new(enum e_ast type);
void	ast_destroy(t_ast *ast);

#endif