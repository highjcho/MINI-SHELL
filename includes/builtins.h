#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

void	mini_env(t_env *env);
void	mini_pwd(void);
void	mini_echo(t_cmd *cmd);

#endif
