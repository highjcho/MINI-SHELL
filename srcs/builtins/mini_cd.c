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
		export[1] =	ft_strjoin("OLDPWD=", env->pwd->value);
		free(env->pwd->value); // 기존 pwd 해제 새로 oldpwd 생성하니까 여기 다시 생각
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
	free(env->old_pwd); // 기존 old_pwd가 이미 존재했으면 기존 old_pwd 해제하고
	env->old_pwd = env->pwd; // old_pwd에 기존 pwd value 연결
	return (TRUE);
}

static int	change_dir(t_env *env, char *new_dir)
{
	int		check;
	char	*tmp;

	if (!new_dir || !ft_strcmp(new_dir, "~"))
		check = chdir(get_env_value(env, "HOME")); // cd만 들어올 경우 home으로
	else if (!ft_strncmp("~/", new_dir, 2)) // ~/desktop ㅇㅣ런식으로 들어올 경우 ~치환
	{
		tmp = ft_strjoin(get_env_value(env, "HOME"), &new_dir[1]);
		if (!tmp)
			return (FALSE);
		free(new_dir);
		new_dir = tmp;
		check = chdir(new_dir);
	}
	else
		check = chdir(new_dir); //cd 뒤에 경로가 들어올 경우 해당 주소로 chdir실행
	if (check == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(new_dir, 2);
		ft_putendl_fd(": No such file or directory", 2);
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
