#include "../../includes/utils.h"

t_env_node	*get_key_node(t_env *env, char *key)
{
	t_env_node	*ret;
	
	ret = env->h_node.next;
	while (ret)
	{
		if (!ft_strcmp(key, ret->key))
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}

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
	new->e_flag = 1;
	new->export = export; // 나중에 unset 시 해제를 위해 저장
	new->next = NULL;
	return (SUCCESS);
}

void	free_env_node(t_env_node *node)
{
	free(node->key); // mini_export export[0] || init_env key free
	if (node->e_flag) // export로 추가한 경우에만 value와 export에 대한 해제 필요
	{
		free(node->value); // export[1] free
		free(node->export); // export 이중포인터 free
	}
	free(node); // node free
}