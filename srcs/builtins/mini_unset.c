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

static int	check_error(char *key, int *flag)
{
	int	n;

	n = ft_strlen(key);
	if (key[n - 1] == '=') // key 마지막 글자가 '='이면 에러처리
	{
		*flag = printf("unset: '%s': not a valid identifier", cmd[i]);
		break; // exit 1로 빠져나가야 함. bash: 1: command not found
	}
	return (*flag);
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
		if (check_error(cmd[i], flag));
			break; // flag만 세우고 다음 턴 넘김 일단 다 실행은 시켜주고 에러메시지 출력됨
		prev = find_prev_env(env->h_node.next, cmd[i]);
		if (!prev)
			break; // 노드 없을 때 오류 아님
		disconnect_node(prev, prev->next);
	}
	if (flag)
	{
		printf("bash 1: command not found");
		return (FALSE); // exit code 1로 종료 되어야 함
	}
	return (SUCCESS);
}