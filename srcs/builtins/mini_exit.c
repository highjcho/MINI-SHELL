#include "../../includes/builtins.h"

int	mini_exit(t_env *env, t_ast *ast) //return 하나?
{
	if (!is_long(ast->av[1]))
	{
		printf("%s: numeric argument required\n", ast->av[1]);
		update_exit_code(env, "255");
		exit(ft_atol(env->exit_code));
	}
	else if (ast->ac > 2)
	{
		printf("too many arguments\n");
		update_exit_code(env, "1");
		return (FAIL);
	}
	if (ast->ac == 1)
		exit(EXIT_SUCCESS);
	exit(ft_atol(ast->av[1])); // 오류?? 리턴??
}