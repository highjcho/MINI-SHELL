#include "../../includes/builtins.h"

int	mini_pwd(void)
{
	char	dir[1025]; // size 뭘로? char *getcwd(char *buf(디렉토리 경로 담을 버프), size_t size(버퍼의 크기))
	char	*check;

	ft_bzero(dir, 1025);
	check = getcwd(dir, 1024);
	if (check == NULL)
		return (FAIL);
	/*
	if (dir[1025])
		error_handler("path too long\n"); // size에 대해서 1024byte를 초과할 경우 에러처리??? 파일 최대경로에 대해서 시스템 마다 달라서 디펜스 영역인듯 보임 https://code-examples.net/ko/q/6445ab
	*/
	printf("%s\n", dir);
	return (SUCCESS);
}