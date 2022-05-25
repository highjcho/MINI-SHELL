#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	mini_env(t_env *env);
void	mini_pwd(void);
void	mini_echo(t_cmd *cmd);
void	mini_export(t_env *env, char *export);
void	mini_unset(t_env *env, char *key);

#endif
