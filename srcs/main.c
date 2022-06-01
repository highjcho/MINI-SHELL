#include "../includes/minishell.h"

int main(int ac, char **av, char **envp)
{
	t_env env;
	// t_cmd cmd;


	if (ac != 1)
		return (1);
	(void) av;
	init_env(&env, envp);
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
	t_token_list *list = make_token_list(tokenize(">>> | >>>>"));
	test_token_list(list);
	env_sub(list, &env);
	printf("%d\n",syntax_check(make_ast(list)));
	return (0);
}