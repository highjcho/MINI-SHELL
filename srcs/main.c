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
	mini_export(&env, "a=333");
	mini_export(&env, "b=555");
	mini_export(&env, "c=111");
	mini_env(&env);
	mini_unset(&env, "b");
	printf("\n==========================================\n\n");
	mini_env(&env);
	return (0);
}