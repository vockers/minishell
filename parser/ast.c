#include "parser.h"

#include <stdlib.h>

t_ast	*ast_new(enum e_ast type)
{
	t_ast	*ast;

	ast = (t_ast *)malloc(sizeof(t_ast));
	if (ast == NULL)
		return (NULL);
	ast->value = NULL;
	ast->type = type;
	ast->left = NULL;
	ast->right = NULL;
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
