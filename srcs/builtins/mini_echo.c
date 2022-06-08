#include "../../includes/builtins.h"

static int	check_opt(char *s, int *i)
{
	if (!ft_strncmp(s, "-n", 2))
	{
		(*i)++;
		return (TRUE);
	}
	return (FALSE);
}

int	mini_echo(char **cmd)
{
	int flag;
	int i;

	i = 1;
	flag = check_opt(cmd[i], &i);
	while(cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[++i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	return (SUCCESS);
}
