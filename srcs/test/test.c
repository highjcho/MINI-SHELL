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
	int	i;

	i = -1;
	printf("node = %s", ast->data);
	if (ast->type == PIPELINE)
		printf("  in_fd = %d, out fd = %d",ast->in_fd, ast->out_fd);
	if (ast->file_name)
		printf (", filename = %s",ast->file_name);
	if (ast->av)
	{
		while (ast->av[++i])
		printf(", av[%d] = %s, ",i,ast->av[i]);
	}
	printf("\n");
	if (ast ->left)
	test_ast(ast ->left);
	if (ast ->right)
	test_ast(ast->right);
}