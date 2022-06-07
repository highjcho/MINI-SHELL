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

int is_long(char *s)
{
	unsigned long long	ul;
	int					sign;
	int tmp;
	
	ul = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s)
	{
		if (ft_isdigit(*s) == FALSE)
			return (FALSE);
		tmp = ul;
		ul = (*s - '0') + (ul * 10);
		if (tmp != ul / 10)
			return (FALSE);
		if (ul > LONG_MAX && sign == 1)
			return (FALSE);
		else if (ul - 1 > LONG_MAX && sign == -1)
			return (FALSE);
		s++;
	}
	return (TRUE);	
}

long long ft_atol(char *s)
{
	long long	ul;
	int					sign;
	int tmp;
	
	ul = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (*s)
	{
		tmp = ul;
		ul = (*s - '0') + (ul * 10);
		s++;
	}
	return (ul * sign);
}