#include "../../includes/builtins.h"

int	mini_exit(t_env *env, int errno) //return 하나?
{
	// 할당 해제할 거 다 해제하고
	free_env(env);
	exit(errno);
	return (SUCCESS); // 오류?? 리턴??
}