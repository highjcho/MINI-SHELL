#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int	mini_echo(char **cmd);
int	mini_cd(t_env *env, char **cmd);
int	mini_pwd(void);
int	mini_export(t_env *env, char **cmd);
int	mini_unset(t_env *env, char **cmd);
int	mini_env(t_env *env);
int	mini_exit(t_env *env, int err_no);

#endif
