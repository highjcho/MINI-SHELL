#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	mini_echo(t_cmd *cmd);
int	mini_cd(t_cmd *cmd, t_env *env);
int	mini_pwd(void);
int	mini_export(t_env *env, char *export);
int	mini_unset(t_env *env, char *key);
int	mini_env(t_env *env);
int	mini_exit(t_env *env, int errno);

#endif
