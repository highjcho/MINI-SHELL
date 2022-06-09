#include "../../includes/builtins.h"

int	mini_exit(t_env *env, t_ast *ast)
{
	if (ast->ac == 2 && !is_long(ast->av[1]))
	{
		printf("exit: %s: numeric argument required\nexit\n", ast->av[1]);
		update_exit_code(env, "255");
		exit(ft_atol(env->exit_code->value));
	}
	else if (ast->ac > 2)
	{
		printf("exit: too many arguments\n");
		update_exit_code(env, "1");
		return (FAIL);
	}
	printf("exit\n");
	if (ast->ac == 1)
		exit(EXIT_SUCCESS);
	exit(ft_atol(ast->av[1]));
	return (FALSE);
}
