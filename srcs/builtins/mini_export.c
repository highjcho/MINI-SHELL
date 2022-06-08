#include "../../includes/builtins.h"

static int	empty_value(char	**export)
{
	export[1] = ft_strdup("");
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
	while (cmd[++i])
	{
		if (!find_c(cmd[i], '='))
			continue;
		export = ft_split(cmd[i], '=');
		if (!export)
			return (FAIL);
		if (export[1] == NULL)
			if (!empty_value(export))
				return (FAIL);
		if (!add_env(env, export))
			return (FAIL);
	}
	return (SUCCESS);
}
