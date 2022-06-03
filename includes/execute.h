#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

int execute_builtin(t_env *env, t_ast *ast, int kind)
int	execute_non_builtin(t_env *env, t_ast *ast, char **envp);

#endif