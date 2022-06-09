#include "../../includes/builtins.h"

static t_env_node	*find_prev_env(t_env_node *node, char *key)
{
	if (!node || !(node->next))
		return (NULL);
	while (ft_strcmp(node->next->key, key))
	{
		node = node->next;
		if (!node->next)
			return (NULL);
	}
	return (node);
}

static void	disconnect_node(t_env_node *prev, t_env_node *cur)
{
	prev->next = cur->next;
	cur->next = NULL;
	free_env_node(cur);
}

static int	check_error(char *key)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	while (key[++i])
	{
		if (key[i] == '=')
		{
			flag = printf("unset: '%s': not a valid identifier\n", key);
			break ;
		}
	}
	return (flag);
}

int	mini_unset(t_env *env, char **cmd)
{
	t_env_node	*prev;
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	while (cmd[++i])
	{
		if (check_error(cmd[i]))
		{
			flag = 1;
			continue ;
		}
		prev = find_prev_env(env->h_node.next, cmd[i]);
		if (!prev)
			continue ;
		disconnect_node(prev, prev->next);
	}
	if (flag)
		return (FAIL);
	return (SUCCESS);
}
