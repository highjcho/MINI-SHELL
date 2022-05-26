#include "../../includes/builtins.h"

<<<<<<< HEAD
static int	find_c(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (1);
	}
	return (0);
}

static int	add_env(t_env *env, char **export)
{
=======
static int	add_env(t_env *env, char **export)
{
>>>>>>> ac3c595393aed7cd14313fdbac845de4a8c6c3ee
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

<<<<<<< HEAD
void	mini_export(t_env *env, char *export)
{
	char	**tmp;

	if (!find_c(export, '=')) // key만 들어오면 아무것도 실행하지 않음
		return ;
	tmp = ft_split(export, '=');
	if (tmp[1] == NULL) // key= 까지 들어오면 뒤에를 공백으로 넣어줌
		tmp[1] = ft_strdup(""); // split에서 두번째 문장이 할당이 안되니까,, free오류 방지를 위해..
	if (!add_env(env, tmp))
		error_handler("minishell: allocate fail", errno); 
=======
void	mini_export(t_env *env, char *export) // env 리스트에 추가하기 key=value 형태로 들어오면 스플릿해서 저장해야 하나?
{
	char	**tmp;

	tmp = ft_split(export, '=');
	if (!add_env(env, tmp))
		error_handler("minishell: allocate fail", errno);
>>>>>>> ac3c595393aed7cd14313fdbac845de4a8c6c3ee
}