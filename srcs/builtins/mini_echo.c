#include "../../includes/builtins.h"

static int	check_opt(char *s, int *i)
{
	if (!ft_strncmp(s, "-n", 2)) // echo 이후 첫번째 원소가 -n으로 시작할 경우 (-nnnn 같은 경우도 -n으로 취급)
	{
		(*i)++; // i 하나 밀고
		return (TRUE);
	}
	return (FALSE);
}

int	mini_echo(char **cmd)
{
	int flag;
	int i;

	i = 1;
	flag = check_opt(cmd[i], &i); // cmd[0] = echo,  cmd[1]이 -n인지 검사
	while(cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[++i]) // 다음 cmd가 존재하면 공백 출력
			printf(" ");
	}
	if (!flag) // -n 옵션에 따라 개행 출력
		printf("\n");
	return (SUCCESS); // ㅇㅔ코가 실패하는 경우?
}