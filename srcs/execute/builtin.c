#include "../../includes/execute.h"

static int	do_builtin(t_env *env, t_ast *ast, int kind)
{
	int	check;

	if (kind == 1)
		check = mini_echo(ast->av);
	else if (kind == 2)
		check = mini_cd(env, ast->av);
	else if (kind == 3)
		check = mini_pwd();
	else if (kind == 4)
		check = mini_export(env, ast->av);
	else if (kind == 5)
		check = mini_unset(env, ast->av);
	else if (kind == 6)
		check = mini_env(env);
	else
		check = mini_env(env, errno);
	// if (check == FALSE) // 인 경우에 뭘 할 것인가? 파이프가 있을 경우 그냥 다음 cmd를 실행하는데,, 오류메시지를 출력하면 fd[1]에 기록됨,,,, perror 허용함수에 없음.. 우짜지.
	return (check); // 얘를 어떻게 활용해야 할까,,,, ㅠ
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

