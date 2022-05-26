#include "../includes/minishell.h"
#include "../libft/libft.h"

int main(int ac, char **av, char **envp)
{
	t_env env;
	
	if (ac != 1)
		return (1);
	(void) av;
	// (void) envp;
	// printf("1: ");
	// mini_pwd();
	// chdir("..");
	// printf("2: ");
	// mini_pwd();
	if (!init_env(&env, envp))
		error_handler("minishell: allocate fail", errno);
	// printf("%s=%s\n", env.old_pwd->key, env.old_pwd->value);
	// printf("%s=%s", env.pwd->key, env.pwd->value);
	t_token_list *list = make_token_list(tokenize("ls -a -l >> a < b > c | grep "" | cat << x > y"));
	make_ast(list);
	return (0);
}