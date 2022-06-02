#include "../../includes/redirect.h"

int	dup_fd(int from_fd, int to_fd)
{
	int	dup_ret;

	dup_ret = dup2(from_fd, to_fd);
	if (from_fd != STDIN_FILENO && from_fd != STDOUT_FILENO)
		close(from_fd);
	if (dup_ret < 0)
		return (FALSE); // 여기서 바로 종료 시키는 게 나을듯,, 안그러면 execute쪽에서 너무 귀찮아 짐
	return (TRUE);
}