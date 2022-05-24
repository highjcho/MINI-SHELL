#include "../../includes/init.h"

static int	ft_key_len(char *key)
{
	int	i;

	i = 0;
	while (key[i] && key[i] != '=')
		i++;
	// if (key[i] == 0) // = 이 없는 환경변수는 없으니 예외처리 안해도 되겠지?
	// 	return (-1);
	return (i);
}

static int	add_env(t_env *env, char *key)
{
	t_env_node	*prev;
	t_env_node	*new;

	new = malloc(sizeof(t_env_node));
	if (!new)
		return (FAIL);
	prev = &(env->h_node);
	while (prev->next)
		prev = prev->next;
	new->key = key;
	new->value = getenv(key);
	prev->next = new;
	new->next = NULL;
	return (SUCCESS);
}

static int	set_env(t_env *env, char **envp)
{
	t_env_node	*cur;
	t_env_node	*tmp;
	char		*key;
	int			i;

	i = -1;
	while (envp[++i])
	{
		key = ft_substr(envp[i], 0, ft_key_len(envp[i])); // env = 전까지 복제
		if (!add_env(env, key)) // 추가 실패 시 전체 리스트 free
		{
			cur = env->h_node.next;
			while (cur)
			{
				tmp = cur->next;
				free(tmp);
				cur = tmp;
			}
			free(env);
			return (FAIL);
		}
	}
	return (SUCCESS);
}
	
int	init_env(t_env *env, char **envp)
{
	env = ft_calloc(1, sizeof(t_env));
	if (!env)
		return (FAIL);
	if (!set_env(env, envp))
		return (FAIL);
	return (SUCCESS);
}