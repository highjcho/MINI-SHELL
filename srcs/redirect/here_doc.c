#include "../../includes/redirect.h"

static void	get_line(char *delimiter, char *line, int out_fd)
{
	while (line)
	{
		if (!ft_strcmp(delimiter, line))
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, out_fd);
		free(line);
		line = readline("heredoc> ");
	}
}

int	here_doc(t_ast *pipeline, t_ast *node)
{
	pid_t	pid;
	int		fd[2];
	int		status;
	char	*line;

	if (pipe(fd) < 0)
		return (FALSE);
	pid = fork();
	signal(SIGINT, handle_signal_heredoc);
	signal(SIGQUIT, handle_signal_heredoc);
	if (pid < 0)
		return (FALSE);
	if (pid == 0)
	{
		close(fd[0]);
		line = readline("heredoc> ");
		get_line(node->file_name, line, fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	wait(&status);
	pipeline->in_fd = fd[0];
	return (TRUE);
}
