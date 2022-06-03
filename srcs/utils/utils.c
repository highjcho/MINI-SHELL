#include "../../includes/utils.h"

int	isbuiltin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (2);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (3);
	else if (!ft_strcmp(cmd[0], "export"))
		return (4);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (5);
	else if (!ft_strcmp(cmd[0], "env"))
		return (6);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (7);
	else
		return (0);
}