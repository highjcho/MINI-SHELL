#include "../../includes/utils.h"

int	add_env(t_env *env, char **export)
{
	t_env_node	*prev;
	t_env_node	*new;

	new = malloc(sizeof(t_env_node));
	if (!new)
	{
		double_free(export);
		return (FAIL);
	}
	prev = &(env->h_node);
	while (prev->next)
		prev = prev->next;
	prev->next = new;
	new->key = export[0]; // unset 시 해제
	new->value = export[1]; // unset 시 해제
	new->export = export; // 나중에 unset 시 해제를 위해 저장
	new->next = NULL;
	return (SUCCESS);
}

char	*get_env_value(t_env *env, char *key)
{
	t_env_node	*ret;
	
	if (!key)
		return (NULL);
	ret = env->h_node.next;
	while (ret)
	{
		if (!ft_strcmp(key, ret->key))
			return (ret->value);
		ret = ret->next;
	}
	return (NULL);
}

void	free_env_node(t_env_node *node)
{
	free(node->key); // export[0] free
	free(node->value); // export[1] free
	free(node->export); // export 이중포인터 free
	free(node); // node free
}