#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_env env;
	// t_cmd cmd;


	if (ac != 1)
		return (1);
	(void) av;
	init_env(&env, envp);

	cmd.in_fd = 0;
	cmd.out_fd = -1;
	cmd.cmd = ft_calloc(sizeof(char *), 2);
	for (int i = 0; i < 3; i++)
	{
		if (i == 0)
		{
			cmd.cmd[0] = ft_strdup("echo");
			cmd.cmd[1] = ft_strdup("ppp");
		}
		else if (i == 1)
		{
			cmd.cmd[0] = ft_strdup("cat");
			cmd.cmd[1] = NULL;
		}
		else
		{
			cmd.cmd[0] = ft_strdup("grep");
			cmd.cmd[1] = ft_strdup("p");
			cmd.out_fd = 1; // 마지막은 out_fd를 1로 초기화한 상태에서 들어가는 것이 중요. 파이프에 써지지 않게. 아웃파일 있으면 아웃파일로 교체 될거임
		}
		execute_cmd(&env, &cmd, envp);
		free(cmd.cmd[0]);
		free(cmd.cmd[1]);
		printf("%d\n", i);
	}
	close(cmd.in_fd); // 마지막 pipe_infd 닫아줘야 됨
	free(cmd.cmd);

	// 	printf("%s=%s\n", env.old_pwd->key, env.old_pwd->value);
	// printf("%s=%s\n", env.pwd->key, env.pwd->value);
	// printf("1: ");
	// mini_pwd();
	// cmd.cmd = ft_calloc(sizeof(char *), 2);
	// cmd.cmd[0] = ft_calloc(sizeof(char), 3);
	// cmd.cmd[0] = "cd";
	// cmd.cmd[1] = NULL;
	// cmd.path = NULL;
	// mini_cd(&cmd, &env);
	// printf("2: ");
	// mini_pwd();
	// mini_export(&env, "hyunjcho=hyunjcho");
	// mini_env(&env);
	// printf("==================\n");
	// mini_unset(&env, "hyunjcho");
	// mini_env(&env);
	// t_env_node *tmp = get_key_node(&env, "hyunjcho");
	// printf("%p", tmp);

	char *line = NULL;
	t_token_list *list = NULL;
	t_ast *ast = NULL;
	while (1)
	{
		line = readline("minishell> ");
		list = make_token_list(tokenize(line));
		ast = make_ast(list);
		ast_merge(ast);
		test_ast(ast);
	}
	return (0);
}