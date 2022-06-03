#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

int	execute_cmd(t_env *env, t_cmd *cmd, char **envp);
void ast_exec(t_ast *ast, t_env *env, char **envp);

#endif