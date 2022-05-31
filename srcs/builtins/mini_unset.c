#include "../../includes/builtins.h"

int	mini_unset(t_env *env, char *key)
{
	t_env_node	*prev;
	t_env_node	*cur;
	int			n;

	n = ft_strlen(key);
	if (key[n - 1] == '=') // key 마지막 글자가 '='이면 에러처리
	{
		printf("unset: '%s': not a valid identifier", key);
		return (FAIL); // exit 1로 빠져나가야 함. 뭐뭐 해제해야 할 지 감이 안오넴.. 일단 env 전부 해제해야 하고 토큰들 있으면 해제하고,,,,,
	}
	prev = env->h_node.next;
	while (ft_strcmp(prev->next->key, key)) // 다음 노드의 키와 인자로 받은 key가 일치하기 직전까지 prev 돌리기
	{
		prev = prev->next;
		if (!prev->next)
			return (SUCCESS); // 해당 노드 내에 key가 존재하지 않을 경우
	}
	cur = prev->next; // prev의 다음 노드
	prev->next = cur->next; // prev의 next를 cur의 next로 연결해 주기
	cur->next = NULL;
	free_env_node(cur);
	return (SUCCESS);
}