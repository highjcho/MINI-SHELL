#include "../../includes/test.h"

void test_token_list(t_token_list *list)
{
	while (list)
	{
		printf("token  = %s\ntype = %d\n", list->token.str,list->token.type);
		list = list ->next;
	}
}

void test_ast(t_ast *ast)
{
	printf("node = %s\n", ast->data);
	if (ast ->left)
	test_ast(ast ->left);
	if (ast ->right)
	test_ast(ast->right);
}