#include "../includes/utils.h"

void print_art(void) // 아스키아트 처리
{
	char	*line;
	int		fd;

	fd = open(fd, O_RDONLY);
	if (fd < 0)
		fd_error("msg", errno); // fd 에러처리
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}