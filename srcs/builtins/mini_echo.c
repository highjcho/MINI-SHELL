#include "../../includes/builtins.h"

static int	check_opt(char *s, int *i)
{
	if (!ft_strncmp(s, "-n", 2)) // echo 이후 첫번째 원소가 -n으로 시작할 경우 (-nnnn 같은 경우도 -n으로 취급)
	{
		(*i)++; // i 하나 밀고
		return (1);
	}
	return (0);
}

void	mini_echo(t_cmd *cmd) // 각 빌트인 들어오기 전에 트리에서 cmd 부분만 cmd 구조체에 cmd 저장해 놓기 (echo p"ppp"p 와 같은 경우 mini_echo를 부르는 곳에서 정리를 하고 cmd 구조체를 생성해줘야 할듯)
{
	int flag;
	int i;

	i = 1;
	flag = check_opt(cmd->cmd[i], &i); // cmd[0] = echo,  cmd[1]이 -n인지 검사
	while(cmd->cmd[i])
	{
		printf("%s", cmd->cmd[i]); // "" 안에서 환경변수는 parse 시에 치환? (pipe_x에서는 이미 치환되어 들어왔음)
		if (cmd->cmd[++i]) // 다음 cmd가 존재하면 공백 출력
			printf(" ");
	}
	if (!flag) // -n 옵션에 따라 개행 출력
		printf("\n");
}