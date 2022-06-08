#include "../../includes/execute.h"

int	execute_cmd(t_env *env, t_ast *ast, char **envp)
{
	int	result;

	result = execute_builtin(env, ast);
	if (result == -1) // 빌트인 함수가 아닐 경우
		return (execute_non_builtin(env, ast, envp));
	if (result == FAIL || result == COMMAND_FAIL) // 빌트인 함수에서 실행 오류가 난 경우
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
