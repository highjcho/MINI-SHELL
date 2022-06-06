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

static int	empty_value(char	**export)
{
	export[1] = ft_strdup(""); // split에서 두번째 문장이 할당이 안되니까,, free오류 방지를 위해..
	if (!export[1])
	{
		free(export[0]);
		free(export);
		return (FALSE);
	}
	return (TRUE);
}

int	mini_export(t_env *env, char **cmd)
{
	char	**export;
	int		i;

	i = 0;
	while (cmd[++i]) // [1]부터 존재할 때 까지
	{
		if (!find_c(cmd[i], '=')) // key만 들어오면 아무것도 실행하지 않음 오류아님
			continue;
		export = ft_split(cmd[i], '='); // env 노드에서 각각 주소 관리하기 때문에 여기서 해제 필요 없음
		if (!export)
			return (FAIL);
		if (export[1] == NULL) // key= 까지 들어오면 뒤에를 공백으로 넣어줌
			if (!empty_value(export))
				return (FAIL);
		if (!add_env(env, export))
			return (FAIL); // h - 할당 오류에 대한 errno를 넘겨야 할 지 아니면 export에 대한 오류 코드인 -1을 받아야 하는 지?
	}
	return (SUCCESS);
}
