#include "../../includes/builtins.h"

static int	env_error_print(char *argument)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(argument, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", 2);
	return (COMMAND_FAIL);
}

int	mini_env(t_env *env, t_ast *ast)
{
	t_env_node	*cur;

	if (ast->ac != 1)
		return (env_error_print(ast->av[1]));
	cur = env->h_node.next;
	while (cur)
	{
		if (cur->value == env->exit_code->value)
		{
			cur = cur->next;
			continue ;
		}
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (SUCCESS);
}
