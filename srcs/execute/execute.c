#include "../../includes/execute.h"

int	execute_cmd(t_env *env, t_ast *ast, char **envp)
{
	int	result;

	result = execute_builtin(env, ast);
	if (result == FAIL) // 빌트인 함수에서 실행 오류가 난 경우
	{
		update_exit_code(env, "1");
		result = STDIN_FILENO;
	}
	if (result == -1) // 빌트인 함수가 아닐 경우
		return (execute_non_builtin(env, ast, envp));
	return (result);
}