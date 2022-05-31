#include "../../includes/builtins.h"

static int	find_c(char *s, char c)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == c)
			return (TRUE);
	}
	return (FALSE);
}

int	mini_export(t_env *env, char *new_env)
{
	char	**export;
	t_env_node	*prev;
	t_env_node	*new;

	if (!find_c(new_env, '=')) // key만 들어오면 아무것도 실행하지 않음 오류아님
		return (SUCCESS);
	export = ft_split(new_env, '=');
	if (!export)
		return (FAIL);
	if (export[1] == NULL) // key= 까지 들어오면 뒤에를 공백으로 넣어줌
	{
		export[1] = ft_strdup(""); // split에서 두번째 문장이 할당이 안되니까,, free오류 방지를 위해..
		if (!export[1])
		{
			free(export[0]);
			free(export);
			return (FAIL);
		}
	}
	if (add_env(env, export) == FAIL)
		return (FAIL); // h - 할당 오류에 대한 errno를 넘겨야 할 지 아니면 export에 대한 오류 코드인 -1을 받아야 하는 지?
	return (SUCCESS);
}
