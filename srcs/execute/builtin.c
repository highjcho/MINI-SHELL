#include "../../includes/execute.h"

static int	do_builtin(t_env *env, t_ast *ast, int kind)
{
	if (kind == 1)
		mini_echo(ast->av);
	else if (kind == 2)
		mini_cd(env, ast->av);
	else if (kind == 3)
		mini_pwd();
	else if (kind == 4)
		mini_export(env, ast->av);
	else if (kind == 5)
		mini_unset(env, ast->av);
	else if (kind == 6)
		mini_env(env);
	else
		mini_env(env, errno);
}

int execute_builtin(t_env *env, t_ast *ast, int kind)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	pipe(fd);
	if (ast->out_fd == 0)
		ast->out_fd = fd[1];
	pid = fork();
	if (pid < 0)
		return (FALSE);
	if (pid == 0)
	{
		close(fd[0]);
		dup_fd(ast->in_fd, STDIN_FILENO);
		dup_fd(ast->out_fd, STDOUT_FILENO);
		do_builtin(env, ast, kind); // cmd가 /bin/cd 이렇게 들어올 경우 어떻게 처리할 지?
	}
	close(fd[1]);
	wait(&status);
	return (fd[0]);
}

