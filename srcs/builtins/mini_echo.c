#include "../../includes/builtins.h"

int check_opt(char *s, int *i)
{
	if (!strncmp(s, "-n", 2)) // echo 이후 첫번째 원소가 -n으로 시작할 경우 (-nnnn 같은 경우도 -n으로 취급)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

void mini_echo(t_token *token)
{
	int flag;
	int i;

	i = 1;
	flag = check_opt(token->str[i], &i); // pipe없이 빌트인함수만 들어왔을 경우 토큰상태에서 검사, redirection은 ast를 순회해야 하나,, ast가 명령어 부분만 보내주나?
	while(token->str[i])
	{
		printf("%s", token->str[i]); // "" 안에서 환경변수는 parse 시에 치환? (pipe_x에서는 이미 치환되어 들어왔음)
		if (token->str[++i])
			printf(" ");
	}
	if (!flag)
		printf("\n");
}