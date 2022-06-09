#include "../../includes/utils.h"

static int	update_value(t_env *env, char **export)
{
	t_env_node	*cur;

	cur = get_env_node(env, export[0]);
	free(cur->value);
	free(export[0]);
	cur->value = export[1];
	return (TRUE);
}

int	add_env(t_env *env, char **export)
{
	t_env_node	*prev;
	t_env_node	*new;

	if (get_env_node(env, export[0]))
		return (update_value(env, export));
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
	new->key = export[0];
	new->value = export[1];
	free(export);
	new->next = NULL;
	return (TRUE);
}

int	update_exit_code(t_env *env, char *exit_code)
{
	free(env->exit_code->value);
	env->exit_code->value = ft_strdup(exit_code);
	if (!env->exit_code->value)
		return (FALSE);
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

t_env_node	*get_env_node(t_env *env, char *key)
{
	t_env_node	*ret;

	if (!key)
		return (NULL);
	ret = env->h_node.next;
	while (ret)
	{
		if (!ft_strcmp(key, ret->key))
			return (ret);
		ret = ret->next;
	}
	return (NULL);
}
