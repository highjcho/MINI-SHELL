#include "../../includes/redirect.h"

static void	get_line(char *delimiter, char *line, int del_len, int out_fd)
{
	(void) del_len;
	while (line)
	{
		if (!ft_strcmp(delimiter, line))
		//if ((del_len + 1 == ft_strlen(line)) && !ft_strncmp(delimiter, line, del_len)) // line 개행 제외하고 비교
		{
			free(line);
			break;
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
		get_line(node->file_name, line, ft_strlen(node->file_name), fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	wait(&status);
	pipeline->in_fd = fd[0];
	return (TRUE);
}

void	redirect_in(t_ast *pipeline, t_ast *node) // 파일 오픈 오류처리 필요 void->int? 재귀에서 어떻게 처리한담..
{
	if (!ft_strcmp("<<", node->data))
	{
		if (pipeline->in_fd != STDIN_FILENO)
			close(pipeline->in_fd);
		here_doc(pipeline, node);
	}
	else if (!ft_strcmp("<", node->data))
	{
		if (pipeline->in_fd != 0)
			close(pipeline->in_fd);
		pipeline->in_fd = open(node->file_name, O_RDONLY);
	}
	else if (!ft_strcmp("<>", node->data)) // 이거는 syntax 오류에서 걷는 것이 맞지 않나?
		pipeline->in_fd = -1;
	if (node->right)
		redirect_in(pipeline, node->right);
}


void	redirect_out(t_ast *pipeline, t_ast *node)
{
	if (!ft_strncmp(">",node->data, ft_strlen(node->data)))
	{
		if (pipeline->out_fd != 1)
			close(pipeline->out_fd);
		pipeline->out_fd = open(node->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else if (!ft_strncmp(">>", node->data, ft_strlen(node->data)))
	{
		if (pipeline->out_fd != 1)
			close(pipeline->out_fd);
		pipeline->out_fd = open(node->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else if (!ft_strncmp("><", node->data, ft_strlen(node->data)))
		pipeline->in_fd = -1;
	if (node->right)
		redirect_out(pipeline, node->right);
}



void ast_redirect_process(t_ast *ast)
{
	if (ast->type == PIPELINE)
	{
		if (ast->left)
		{
			redirect_in(ast, ast->left);
			redirect_out(ast, ast->left);
		}
	}
}