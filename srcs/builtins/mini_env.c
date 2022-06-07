#include "../../includes/builtins.h"

static void	env_error(t_env *env, char *argument)
{
	ft_putstr_fd("env: ", STDERR_FILENO);
	ft_putstr_fd(argument, STDERR_FILENO);
	ft_putendl_fd(": No such file or directory", 2);
	update_exit_code(env, "127");
}

int	mini_env(t_env *env, t_ast *ast)
{
	t_env_node	*cur;
	
	if (ast->ac != 1)
		env_error(env, ast->av[1]);
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