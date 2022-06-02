#include "../../includes/init.h"

static int	set_path(t_env *env)
{
	env->path = ft_split(get_key_node(env, "PATH")->value, ':');
	if (!env->path)
	{
		error_handler("pipex: allocate failed", errno);
		return (FALSE);
	}
	return (TRUE);
}

static int	init_add_env(t_env *env, char **export)
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
	new->key = export[0]; // unset 시 해제 필요
	new->value = export[1]; // unset 시 해제 필요
	new->export = export;
	new->next = NULL;
	if (!ft_strcmp(export[0], "PWD")) // pwd 위치 저장
		env->pwd = new;
	if (!ft_strcmp(export[0], "OLDPWD")) // old_pwd 위치 저장
		env->old_pwd = new;
	return (TRUE);
}

static int	set_env(t_env *env, char **envp)
{
	char		**export;
	int			i;

	i = -1;
	while (envp[++i])
	{
		export = ft_split(envp[i], '=');
		if (!export)
			return (FALSE);
		if (!init_add_env(env, export)) // 추가 실패 시 전체 리스트 free, getenv도 할당인가? 해제를 해줘야 하나?
		{
			free_env(env);
			return (FALSE);
		}
	}
	return (TRUE);
}
	
int	init_env(t_env *env, char **envp)
{
	env->h_node.next = NULL;
	env->pwd = NULL;
	env->old_pwd = NULL;
	if (!set_env(env, envp))
		return (FAIL);
	if (!set_path(env))
		return (FAIL);
	return (SUCCESS);
}