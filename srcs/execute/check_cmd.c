#include "../../includes/execute.h"

static int	isbuiltin(char	*cmd)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (2);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (3);
	else if (!ft_strcmp(cmd[0], "export"))
		return (4);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (5);
	else if (!ft_strcmp(cmd[0], "env"))
		return (6);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (7);
	else
		return (0);
}

int	execute_cmd(t_env *env, t_ast *ast, char **envp)
{
	int	kind;

	kind = isbuiltin(ast->av[1]);
	if (kind)
		execute_builtin(env, ast, kind);
	else
		execute_non_builtin(env, ast, envp);
}