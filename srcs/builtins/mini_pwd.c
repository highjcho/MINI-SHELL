#include "../../includes/builtins.h"

int	mini_pwd(void)
{
	char	dir[4096]; // size 뭘로? char *getcwd(char *buf(디렉토리 경로 담을 버프), size_t size(버퍼의 크기))
	char	*check;

	ft_bzero(dir, 4096); // https://code-examples.net/ko/q/6445ab bash 파일 최대경로 4096byte.. 디펜스 영역인듯 보임
	check = getcwd(dir, 4096);
	if (check == NULL)
		return (FAIL);
	printf("%s\n", dir);
	return (SUCCESS);
}
