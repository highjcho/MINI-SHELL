/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:11:12 by hyunjcho          #+#    #+#             */
/*   Updated: 2022/06/09 11:11:14 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static int	do_builtin(t_env *env, t_ast *ast, int kind)
{
	int	check;

	if (kind == 1)
		check = mini_env(env, ast);
	else if (kind == 2)
		check = mini_pwd();
	else
		check = mini_echo(ast->av);
	return (check);
}

static int	write_pipe(t_env *env, t_ast *ast, int kind)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) < 0)
		return (FALSE);
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
		exit(do_builtin(env, ast->right, kind));
	}
	close(fd[1]);
	wait(&status);
	if (status >> 8 == FAIL)
		return (FAIL);
	else if (status >> 8 == COMMAND_FAIL)
		return (COMMAND_FAIL);
	return (fd[0]);
}

int	execute_builtin(t_env *env, t_ast *ast)
{
	if (ast->right)
	{
		if (!ft_strcmp(ast->right->av[0], "cd"))
			return (mini_cd(env, ast->right->av));
		else if (!ft_strcmp(ast->right->av[0], "export"))
			return (mini_export(env, ast->right->av));
		else if (!ft_strcmp(ast->right->av[0], "unset"))
			return (mini_unset(env, ast->right->av));
		else if (!ft_strcmp(ast->right->av[0], "exit"))
			return (mini_exit(env, ast->right));
		else if (!ft_strcmp(ast->right->av[0], "env"))
			return (write_pipe(env, ast, 1));
		else if (!ft_strcmp(ast->right->av[0], "pwd"))
			return (write_pipe(env, ast, 2));
		else if (!ft_strcmp(ast->right->av[0], "echo"))
			return (write_pipe(env, ast, 3));
	}
	return (-1);
}
