#include "../../includes/execute.h"

static int	do_builtin(t_env *env, t_ast *ast, int kind) // 이로직이 조금 조잡함 ㅎ
{
	int	check;

	if (kind == 1)
		check = mini_export(env, ast->av);
	else if (kind == 2)
		check = mini_pwd();
	else
		check = mini_echo(ast->av);
	// if (check == FALSE) // 인 경우에 뭘 할 것인가? 파이프가 있을 경우 그냥 다음 cmd를 실행하는데,, 오류메시지를 출력하면 fd[1]에 기록됨,,,, perror 허용함수에 없음.. 우짜지.
	return (check); // 얘를 어떻게 활용해야 할까,,,, ㅠ
}

static int	write_pipe(t_env *env, t_ast *ast, int kind)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	int		check;

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
		check = do_builtin(env, ast->right, kind); // cmd가 /bin/cd 이렇게 들어올 경우 어떻게 처리할 지?
		exit(check); // status를 활용해야 하는가? status 처리 알아야겠다..둪'
	}
	close(fd[1]);
	wait(&status);
	return (fd[0]);
}

int	execute_builtin(t_env *env, t_ast *ast)
{
	if (!ft_strcmp(ast->right->av[0], "cd"))
		return (mini_cd(env, ast->av));
	else if (!ft_strcmp(ast->right->av[0], "export"))
		return (mini_export(env, ast->av));
	else if (!ft_strcmp(ast->right->av[0], "unset"))
		return (mini_unset(env, ast->av));
	else if (!ft_strcmp(ast->right->av[0], "exit"))
		return (mini_exit(env, errno));
	else if (!ft_strcmp(ast->right->av[0], "env"))
		return (write_pipe(env, ast, 1));
	else if (!ft_strcmp(ast->right->av[0], "pwd"))
		return (write_pipe(env, ast, 2));
	else if (!ft_strcmp(ast->right->av[0], "echo"))
		return (write_pipe(env, ast, 3));
	else
		return (-1);
}