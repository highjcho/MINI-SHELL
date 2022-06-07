#include "../../includes/utils.h"

int	find_c(char *s, char c)
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

int	update_exit_code(t_env *env, char *exit_code)
{
	free(env->exit_code);
	env->exit_code = ft_strdup(exit_code);
	if (!env->exit_code)
		return (FALSE);
	return (TRUE);
}