#include "../../includes/builtins.h"

int	mini_env(t_env *env)
{
	t_env_node	*cur; // env에 인자가 들어오면 fail mini_env를 부르는 시점에 검사를 해야할 듯
	
	cur = env->h_node.next;
	while (cur)
	{
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (SUCCESS);
}