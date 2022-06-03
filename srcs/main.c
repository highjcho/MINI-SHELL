#include "../includes/minishell.h"

static void	excute_line(t_env *env, t_ast *ast, char **envp)
{
	int	i;
	int	next_in_fd;

	i = -1;
	next_in_fd = STDIN_FILENO;
	while(pl)
	{
		ast->in_fd = next_in_fd;
		if (pl 마지막)
			ast->out_fd = 1;
		set_redirect_process(&ast);
		next_in_fd = execute_cmd(env, ast->right, envp);
	}
	if (next_in_fd != STDIN_FILENO)
		close(next_in_fd);
	// all_free(); 한 텀 끝내는 로직 필요
}

int main(int ac, char **av, char **envp)
{
	t_env			env;
	t_token_list	list;
	t_ast			ast;
	char			*line;

	if (ac != 1)
		return (0);
	(void) av;
	init_env(&env, envp);
	while (1)
	{
		line = readline("minishell> ");
		list = make_token_list(tokenize(line));
		ast = make_ast(&list);
		ast_merge(&ast);
		excute_line(env, ast, envp);
	}
	return (0);
}