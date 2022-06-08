#include "../../includes/utils.h"

void setechoctl(int flag)
{
	struct termios new_term;

	tcgetattr(STDIN_FILENO, &new_term);
	if (flag)
		new_term.c_lflag &= ~(ECHOCTL);
	else
		new_term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
}