#include "../../includes/builtins.h"

static t_env_node	*find_prev_env(t_env_node *node, char *key)
{
	if (!node)
		return (NULL);
	while (ft_strcmp(node->next->key, key)) // 다음 노드의 키와 인자로 받은 key가 일치하기 직전까지 prev 돌리기
	{
		node = node->next;
		if (!node->next)
			return (NULL); // 해당 노드 내에 key가 존재하지 않을 경우
	}
	return (node);
}

static void	disconnect_node(t_env_node *prev, t_env_node *cur)
{
	prev->next = cur->next; // prev의 next를 cur의 next로 연결해 주기
	cur->next = NULL;
	free_env_node(cur);
}

static int	check_error(t_env *env, char *key)
{
	int	flag;
	int	n;
	int	i;

	flag = 0;
	n = ft_strlen(key);
	i = -1;
	while (++i < n)
	{
		if (key[i] == '=') // key에 '='이 포함되어 있으면 에러 처리
		{
			flag = printf("unset: '%s': not a valid identifier\n", key);
			update_exit_code(env, "1");
			break;
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
		if (check_error(env, cmd[i]))
		{
			flag = 1;
			continue; // flag만 세우고 다음 턴 넘김 일단 다 실행은 시켜주고 에러메시지 출력됨
		}
		prev = find_prev_env(env->h_node.next, cmd[i]);
		if (!prev)
			continue; // 노드 없을 때 오류 아님
		disconnect_node(prev, prev->next);
	}
	if (flag)
		return (FAIL);
	return (SUCCESS);
}