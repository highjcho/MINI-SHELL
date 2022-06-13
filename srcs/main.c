#include "../includes/minishell.h"

static void	excute_line(t_env *env, t_pl_list *list, char **envp)
{
	int	next_in_fd;
	int	i;
	int	flag;

	next_in_fd = STDIN_FILENO;
	i = 0;
	flag = FALSE;
	while(list)
	{
		list->pipeline->in_fd = next_in_fd;
		if (!list->next)
			list->pipeline->out_fd = 1;
		ast_redirect_process(list->pipeline);
		// test_ast(list->pipeline);
		if (list->pipeline->in_fd == -1 || list->pipeline->out_fd == -1)
		{
			update_exit_code(env, "1");
			list = list->next;
			next_in_fd = fork_process();
			continue;
		}
		if (i == 0 && !(list->next))
			flag = TRUE;
		next_in_fd = execute_cmd(env, list->pipeline, envp, flag);
		list = list->next;
		i++;
	}
	if (next_in_fd != STDIN_FILENO)
		close(next_in_fd);
}

static void	print_cur_directory(char *pwd)
{
	int	len;
	int	i;

	len = ft_strlen(pwd);
	i = len;
	while (pwd[--i])
	{
		if (pwd[i] == '/')
			break ;
	}
	printf("[petitshell] %s ", pwd + i + 1);
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
	print_art();
	while (1)
	{
		print_cur_directory(get_env_value(&env, "PWD"));
		line = readline("% ");
		if (!line)
		{
			printf("petitshell> exit\n");
			exit(1);
		}
		else if (!*line)
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (main_init(line, &info) == FAIL)
		{
			free(line);
			continue;
		}
		// test_ast(info.ast);
		excute_line(&env, info.pl->next, envp);
		// all_free(&info);
		free(line);
	}
	return (0);
}