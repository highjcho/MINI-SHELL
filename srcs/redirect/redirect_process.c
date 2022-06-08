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

static int	here_doc(t_ast *pipeline, t_ast *node)
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

void	redirect_in(t_ast *pipeline, t_ast *node)
{
	if (!ft_strcmp("<<", node->data))
	{
		if (pipeline->in_fd != STDIN_FILENO)
			close(pipeline->in_fd);
		here_doc(pipeline, node);
	}
	else if (!ft_strcmp("<", node->data))
	{
		if (pipeline->in_fd != STDIN_FILENO)
			close(pipeline->in_fd);
		pipeline->in_fd = open(node->file_name, O_RDONLY);
	}
}

void	redirect_out(t_ast *pipeline, t_ast *node)
{
	if (!ft_strncmp(">", node->data, ft_strlen(node->data)))
	{
		if (pipeline->out_fd > STDOUT_FILENO)
			close(pipeline->out_fd);
		pipeline->out_fd = open(node->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else if (!ft_strncmp(">>", node->data, ft_strlen(node->data)))
	{
		if (pipeline->out_fd > STDOUT_FILENO)
			close(pipeline->out_fd);
		pipeline->out_fd = open(node->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	}
}

void	redirect_process(t_ast *ast, t_ast *node)
{
	if (node -> data && node->data[0] == '<')
		redirect_in(ast, node);
	else if (node -> data && node->data[0] == '>')
		redirect_out(ast, node);
	if (node->right)
		redirect_process(ast, node->right);
}

void	ast_redirect_process(t_ast *ast)
{
	if (ast->type == PIPELINE)
	{
		if (ast->left)
			redirect_process(ast, ast->left);
	}
}
