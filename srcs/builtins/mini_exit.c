#include "../../includes/builtins.h"

int	mini_exit(t_env *env, t_ast *ast) //return 하나?
{
	// 할당 해제할 거 다 해제하고
	// int	i;
	// int	flag;

	// i = 1;
	// if (ast->av[i])
	// while (ast->av[i])
	// 	i++;
	// if (i > 1)
	// {
	// 	j = -1;
	// 	while (ast->av[i][++j])
	// 	{
	// 		if (!ft_isdigit(ast->av[i][j]))
	// 			break;
	// 	}
	// 	if (ast->av[i][j] == NULL)
	// 	{
	// 		printf("too many arguments\n");
	// 		update_exit_code(env, "1");
	// 		return (FAIL);
	// 	}
	// 	else
	// 	{
	// 		printf("%s: numeric argument required\n", ast->av[1]);
	// 		update_exit_code(env, "255");
	// 	}
	// }
	// else
	// {

	// }
	// free_env(env);
	exit(EXIT_SUCCESS);
	// exit(ft_atoi(env->exit_code));
	return (FAIL); // 오류?? 리턴??
}