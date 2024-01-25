/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ast.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: vockers <vockers@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/25 16:21:51 by vockers       #+#    #+#                 */
/*   Updated: 2024/01/25 16:21:51 by vockers       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#include <stdlib.h>

t_ast	*ast_new(enum e_ast type)
{
	t_ast	*ast;

	ast = (t_ast *)ft_calloc(1, sizeof(t_ast));
	if (ast == NULL)
		return (NULL);
	ast->type = type;
	return (ast);
}

void	ast_destroy(t_ast *ast)
{
	if (ast == NULL)
		return ;
	ast_destroy(ast->left);
	ast_destroy(ast->right);
	free(ast->value);
	free(ast);
}
