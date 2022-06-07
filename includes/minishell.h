#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "struct.h"
# include "init.h"
# include "builtins.h"
# include "utils.h"
# include "parse.h"
# include "redirect.h"
# include "execute.h"
# include "error.h"
# include "../libft/libft.h"
# include "test.h"

# define SUCCESS 0
# define FAIL 1
# define TRUE 1
# define FALSE 0
# define COMMAND_FAIL 127
# define LONG_MAX 9223372036854775807
# define LONG_MIN -9223372036854775808

#endif
