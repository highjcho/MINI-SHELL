#include "../../includes/execute.h"

int	execute_cmd(t_env *env, t_ast *ast, char **envp)
{
	int	result;

	result = execute_builtin(env, ast);
	if (result == -1)
		return (execute_non_builtin(env, ast, envp));
	if (result == FAIL || result == COMMAND_FAIL)
	{
		if (result == FAIL)
			update_exit_code(env, "1");
		else
			update_exit_code(env, "127");
		return (STDIN_FILENO);
	}
	update_exit_code(env, "0");
	return (result);
}
