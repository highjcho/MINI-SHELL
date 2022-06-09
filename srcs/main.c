#include "../includes/minishell.h"

static void	excute_line(t_env *env, t_pl_list *list, char **envp)
{
	int	i;
	int	next_in_fd;

	i = -1;
	next_in_fd = STDIN_FILENO;
	while(list)
	{
		list->pipeline->in_fd = next_in_fd;
		if (!list->next)
			list->pipeline->out_fd = 1;
		ast_redirect_process(list->pipeline);
		// test_ast(list->pipeline);
		if (list->pipeline->in_fd == -1)
		{
			update_exit_code(env, "1");
			list = list->next;
			next_in_fd = fork_process();
			continue;
		}
		next_in_fd = execute_cmd(env, list->pipeline, envp);
		list = list->next;
	}
	if (next_in_fd != STDIN_FILENO)
		close(next_in_fd);
	//all_free(); 한 텀 끝내는 로직 필요
}

int main(int ac, char **av, char **envp)
{
	t_env			env;
	char			*line;
	t_info			info;

	if (ac != 1)
		return (0);
	line = NULL;
	set_init(&env, envp, av);
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("minishell> exit\n");
			exit(1);
		}
		else if (!*line)
			continue ;
		add_history(line);
		if (main_init(line, &info) == FAIL)
		{
			free(line);
			continue;
		}
		// test_ast(info.ast);
		excute_line(&env, info.pl->next, envp);
		all_free(&info);
		free(line);
	}
	return (0);
}