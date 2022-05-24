#include "../includes/minishell.h"
#include "../libft/libft.h"

int main(int ac, char **av, char **envp)
{
	t_env env;
	
	if (ac != 1)
		return (1);
	(void) av;
	// printf("1: ");
	// mini_pwd();
	// chdir("..");
	// printf("2: ");
	// mini_pwd();
	if (!init_env(&env, envp))
		error_handler("minishell: allocate fail", errno);
	mini_env(&env);
	return (0);
}