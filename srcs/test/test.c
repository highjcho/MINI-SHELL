#include "../../includes/test.h"

void test_token_list(t_token_list *list)
{
	while (list)
	{
		printf("token  = %s\ntype = %d\n", list->token.str,list->token.type);
		list = list ->next;
	}
}