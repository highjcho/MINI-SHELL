#include "../../includes/execute.h"

static int	set_path(t_env *env)
{
	env->path = ft_split(get_env_value(env, "PATH"), ':');
	if (!env->path)
		return (FALSE);
	return (TRUE);
}

static int	need_to_make_path(t_env *env, t_ast *ast, char **envp)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!set_path(env))
		exit(FAIL);
	while (env->path[++i])
	{
		tmp = ft_strjoin("/", ast->av[0]);
		if (!tmp)
			exit(FAIL);
		ast->path = ft_strjoin(env->path[i], tmp);
		if (!ast->path)
			exit(FAIL);
		free(tmp);
		execve(ast->path, ast->av, envp);
		free(ast->path);
	}
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(ast->av[0], 2);
	ft_putendl_fd(": command not found", 2);
	exit(COMMAND_FAIL);
}

static int	have_path(t_env *env, t_ast *ast, char **envp)
{
	if (!ft_strncmp("~/", ast->av[0], 2))
	{
		ast->path = ft_strjoin(get_env_value(env, "HOME"), &ast->av[0][1]);
		if (!ast->path)
			exit(FAIL);
	}
	else
	{
		ast->path = ft_strdup(ast->av[0]);
		if (!ast->path)
			exit(FAIL);
	}
	execve(ast->path, ast->av, envp);
	ft_putstr_fd(ast->av[0], 2);
	ft_putendl_fd(": command not found\n", 2);
	exit(COMMAND_FAIL);
}

int	execute_non_builtin(t_env *env, t_ast *ast, char **envp)
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
		if (find_c(ast->right->av[0], '/'))
			have_path(env, ast->right, envp);
		else
			need_to_make_path(env, ast->right, envp);
	}
	close(fd[1]);
	wait(&status);
	update_exit_code(env, ft_itoa(status >> 8));
	return (fd[0]);
}
