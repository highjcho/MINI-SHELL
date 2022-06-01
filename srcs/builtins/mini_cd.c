#include "../../includes/builtins.h"

static int	set_old_pwd(t_env *env)
{
	char	*old_pwd;

	if (!env->old_pwd)
	{
		old_pwd = ft_strjoin("OLDPWD=", env->pwd->value);
		if (mini_export(env, old_pwd) == FAIL)
		{
			free(old_pwd);
			return (FALSE);
		} // export 활용해도 되겠지?
	}
	free(env->old_pwd->value); // 기존 old_pwd가 이미 존재했으면 기존 old_pwd 해제하고
	env->old_pwd->value = env->pwd->value; // old_pwd에 기존 pwd 연결
	return (TRUE);
}

static int	change_dir(t_env *env, char *new_dir)
{
	int		check;

	if (!new_dir)
		check = chdir(get_env_value(env, "HOME"));
	else
		check = chdir(new_dir);
	if (check == FAIL)
		return (FALSE);
	return (TRUE);
}

int	mini_cd(t_cmd *cmd, t_env *env)
{
	char	dir[1025];
	char	*check;

	if (!change_dir(env, cmd->cmd[1])) // cd만 들어올 경우 home으로, cd 뒤에 경로가 들어올 경우 해당 주소로 chdir실행
	{
		free(cmd->cmd[0]);
		free(cmd);
		return (FAIL);
	}
	ft_bzero(dir, 1025);
	check = getcwd(dir, 1024);
	if (!check)
		return (FAIL);
	if (!set_old_pwd(env))
		return (FAIL);
	env->pwd->value = ft_strdup(dir);
	if (!env->pwd->value)
		return (FAIL);
	return (SUCCESS);
}

/*
1. 두번째 인자가 뭔지에 따라 chdir 실행
2. 현재 pwd->old_pwd로 밸류 바꾸고
3. 현재 pwd는 getcwd로 받아올 것
*/