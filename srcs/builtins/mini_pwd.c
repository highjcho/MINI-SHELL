#include "../../includes/builtins.h"

int	mini_pwd(void)
{
	char	dir[4096];
	char	*check;

	ft_bzero(dir, 4096);
	check = getcwd(dir, 4096);
	if (check == NULL)
		return (FAIL);
	printf("%s\n", dir);
	return (SUCCESS);
}
