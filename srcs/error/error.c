#include "../../includes/error.h"

void	error_handler(char *msg, int err_no)
{
	printf("%s\n", msg);
	strerror(err_no);
	exit(err_no);
}