/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:09:41 by hyunjcho          #+#    #+#             */
/*   Updated: 2022/06/09 11:09:47 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	set_old_pwd(t_env *env)
{
	char	**export;

	if (!env->old_pwd)
	{
		export = ft_calloc(3, sizeof(char *));
		if (!export)
			return (FALSE);
		export[0] = ft_strdup("export");
		export[1] = ft_strjoin("OLDPWD=", env->pwd->value);
		free(env->pwd->value);
		if (!export[0] || !export[1])
		{
			double_free(export);
			return (FALSE);
		}
		if (mini_export(env, export) == FAIL)
		{
			double_free(export);
			return (FALSE);
		}
		return (TRUE);
	}
	free(env->old_pwd->value);
	env->old_pwd->value = env->pwd->value;
	return (TRUE);
}

static int	change_dir(t_env *env, char *new_dir)
{
	int		check;
	char	*tmp;

	if (!new_dir || !ft_strcmp(new_dir, "~"))
		check = chdir(get_env_value(env, "HOME"));
	else if (!ft_strncmp("~/", new_dir, 2))
	{
		tmp = ft_strjoin(get_env_value(env, "HOME"), &new_dir[1]);
		if (!tmp)
			return (FALSE);
		free(new_dir);
		new_dir = tmp;
		check = chdir(new_dir);
	}
	else
		check = chdir(new_dir);
	if (check == -1)
	{
		ft_putstr_fd("petitshell: cd: ", STDERR_FILENO);
		ft_putstr_fd(new_dir, STDERR_FILENO);
		ft_putendl_fd(": No such file or directory", STDERR_FILENO);
		return (FALSE);
	}
	return (TRUE);
}

int	mini_cd(t_env *env, char **cmd)
{
	char	dir[4096];
	char	*check;

	if (!change_dir(env, cmd[1]))
		return (FAIL);
	ft_bzero(dir, 4096);
	check = getcwd(dir, 4096);
	if (!check)
		return (FAIL);
	if (!set_old_pwd(env))
		return (FAIL);
	env->pwd->value = ft_strdup(dir);
	if (!env->pwd)
		return (FAIL);
	return (SUCCESS);
}
