#include "../../includes/signal.h"


void sig_handler(int sig)
{
	if (sig == SIGINT)
	{	
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b\n");
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 1);
	}
	else if (sig == SIGTERM)
	{

	}
	else if (sig == SIGQUIT)
	{

	}

}

void sig_init(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGTERM, sig_handler);
}