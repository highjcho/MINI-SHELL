#ifndef _MINISHELL_H_
# define _MINISHELL_H_

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/errno.h>
# include "utils.h"
# include "../libft/libft.h"

enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT
};

typedef struct s_token
{
	char	*str;
	enum 	e_token_type;
}	t_token;

#endif