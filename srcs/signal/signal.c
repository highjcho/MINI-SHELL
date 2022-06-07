#include "../../includes/signal.h"

void	handle_signal(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
	{
		if (pid == -1)
		{	
			rl_on_new_line();
			rl_redisplay();
			printf("  \b\b\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			printf("\n");
		}
	}
	else if (signum == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			printf("  \b\b");
		}
		else
		{
			printf("Quit: 3\n");
		}
	}
}

void	signal_init(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	// signal(SIGTERM, handle_signal);
}