#include "../../includes/builtins.h"

void	mini_unset(t_env *env, char *key)
{
	t_env_node	*prev;
	t_env_node	*cur;
	int			n;

	n = ft_strlen(key) + 1;
	prev = env->h_node.next;
	while (ft_strncmp(prev->next->key, key, n)) // 다음 노드의 키와 인자로 받은 key가 일치하기 직전까지 prev 돌리기
		prev = prev->next;
	cur = prev->next; // prev의 다음 노드
	prev->next = cur->next; // prev의 next를 cur의 next로 연결해 주기
	free(cur->key); // export[0] free
	if (cur->e_flag)
	{
		free(cur->value); // export[1] free
		free(cur->export); // export free
	}
	free(cur); // node free
}