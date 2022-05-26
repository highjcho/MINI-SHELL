#include "../../includes/builtins.h"

static int	add_env(t_env *env, char **export)
{
	t_env_node	*prev;
	t_env_node	*new;

	new = malloc(sizeof(t_env_node));
	if (!new)
		return (FAIL);
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

void	mini_export(t_env *env, char *export) // env 리스트에 추가하기 key=value 형태로 들어오면 스플릿해서 저장해야 하나?
{
	char	**tmp;

	tmp = ft_split(export, '=');
	if (!add_env(env, tmp))
		error_handler("minishell: allocate fail", errno);
}