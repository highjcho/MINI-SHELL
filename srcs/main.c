#include "../includes/minishell.h"
#include "../libft/libft.h"

int main(int ac, char **av, char **envp)
{
	if (ac != 1)
		return (1);
	(void) av;
	(void) envp;
	printf("1: ");
	mini_pwd();
	chdir("..");
	printf("2: ");
	mini_pwd();
	return (0);
}