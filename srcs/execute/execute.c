#include "../../includes/execute.h"

int	execute_cmd(t_env *env, t_ast *ast, char **envp)
{
	int	in_fd;

	in_fd = execute_builtin(env, ast);
	if (in_fd == -1)
		return (execute_non_builtin(env, ast, envp));
	return (in_fd);
}