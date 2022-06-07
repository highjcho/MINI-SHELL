#include "../../includes/builtins.h"

int	mini_env(t_env *env, t_ast *ast)
{
	t_env_node	*cur;
	
	if (ast->ac != 1)
	{
		ft_putstr_fd("env: ", STDERR_FILENO);
		ft_putstr_fd(ast->av[1], STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", 2);
		return (COMMAND_FAIL);
	}
	cur = env->h_node.next;
	while (cur)
	{
		if (cur->value == env->exit_code)
		{
			cur = cur->next;
			continue;
		}
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	return (SUCCESS);
}