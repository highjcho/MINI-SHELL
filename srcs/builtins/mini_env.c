#include "../../includes/builtins.h"

int	mini_env(t_env *env)
{
	t_env_node	*cur;
	
	cur = env->h_node.next;
	while (cur)
	{
		if (!ft_strcmp(cur->key, "?"))
		{
			cur = cur->next;
			continue;
		}
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (SUCCESS);
}