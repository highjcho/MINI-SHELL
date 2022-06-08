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
		if (list->pipeline->in_fd == -1)
		{
			update_exit_code(env, "1");
			list = list->next;
			continue;
		}
		next_in_fd = execute_cmd(env, list->pipeline, envp);
		list = list->next;
	}
	if (next_in_fd != STDIN_FILENO)
		close(next_in_fd);
	// all_free(); 한 텀 끝내는 로직 필요
}

int main(int ac, char **av, char **envp)
{
	t_env			env;
	t_token_list	*list;
	t_ast			*ast;
	t_pl_list		*pl;
	char			*line;

	if (ac != 1)
		return (0);
	(void) av;
	init_env(&env, envp);
	g_env = &env;
	signal_init();

	line = NULL;
	setechoctl(1);
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
		list = make_token_list(tokenize(line));
		env_sub(list,&env);
		ast = make_ast(list);
		if(syntax_check(ast) == FAIL)
		{
			update_exit_code(&env, "258");
			continue;
		}
		ast_merge(ast);
		pl = pl_list(ast);
		excute_line(&env, pl->next, envp);
	}
	return (0);
}