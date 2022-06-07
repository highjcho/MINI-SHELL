#include "../../includes/signal.h"


static void	handle_sigint(pid_t pid)
{
	if (pid == -1)
	{
		printf("\b\b  \b\b\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		printf("\n");
	}
}

static void	handle_sigquit(pid_t pid)
{
	if (pid == -1)
		printf("\b\b  \b\b");
	else
	{
		printf("Quit: 3\n");
	}
}

void	handle_signal(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
		handle_sigint(pid);
	else if (signum == SIGQUIT)
		handle_sigquit(pid);
}


void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
}