#include "../../includes/utils.h"

int	add_env(t_env *env, char **export)
{
	t_env_node	*prev;
	t_env_node	*new;

	new = malloc(sizeof(t_env_node));
	if (!new)
	{
		double_free(export);
		return (FALSE);
	}
	prev = &(env->h_node);
	while (prev->next)
		prev = prev->next;
	prev->next = new;
	new->key = export[0]; // unset 시 해제
	new->value = export[1]; // unset 시 해제
	new->export = export; // 나중에 unset 시 해제를 위해 저장
	new->next = NULL;
	return (TRUE);
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

int	update_exit_code(t_env *env, char *exit_code)
{
	free(env->exit_code->value);
	env->exit_code->value = ft_strdup(exit_code);
	if (!env->exit_code->value)
		return (FALSE);
	return (TRUE);
}

void	free_env_node(t_env_node *node)
{
	free(node->key); // export[0] free
	free(node->value); // export[1] free
	free(node->export); // export 이중포인터 free
	free(node); // node free
}
