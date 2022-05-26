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

static int	add_env(t_env *env, char *key, char *value)
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
	new->key = key; // unset 시 해제 필요
	new->value = value;
	new->e_flag = 0;
	new->export = NULL;
	new->next = NULL;
	if (!ft_strncmp(key, "PWD", 4)) // pwd 위치 저장
		env->pwd = new;
	if (!ft_strncmp(key, "OLDPWD", 7)) // old_pwd 위치 저장
		env->old_pwd = new; 
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
		if (!ft_strncmp(key, "_", 2))
			break;
		if (!add_env(env, key, getenv(key))) // 추가 실패 시 전체 리스트 free, getenv도 할당인가? 해제를 해줘야 하나?
		{
			cur = env->h_node.next;
			while (cur)
			{
				tmp = cur->next;
				free(cur->key);
				free(cur);
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
	env->h_node.next = NULL;
	env->pwd = NULL;
	env->old_pwd = NULL;
	if (!set_env(env, envp))
		return (FAIL);
	return (SUCCESS);
}