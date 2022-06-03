#include "../../includes/parse.h"

void	make_pl_list(t_ast *ast, t_pl_list *node)
{
	t_pl_list	*cur;

	cur = NULL;
	if (ast->type == PIPELINE)
	{
		cur = ft_calloc(sizeof(t_pl_list), 1);
		ast_redirect_process(ast);
		cur->pipeline = ast;
		node->next = cur;
	}
	if (!cur)
		cur = node;
	if (ast->left)
		make_pl_list(ast->left, cur);
	if (ast->right)
		make_pl_list(ast->right, cur);
}

t_pl_list *pl_list(t_ast *ast)
{
	t_pl_list	*list;

	list = ft_calloc(sizeof(t_pl_list), 1);
	make_pl_list(ast, list);
	return (list);
}