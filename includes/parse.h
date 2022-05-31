#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

char			**tokenize(char *str);
t_token_list	*make_token_list(char **tokens);
t_ast			*add_pl_node(t_ast *parent, t_ast *child);
t_ast			*add_pipe_node(t_ast *parent, t_ast *child);
t_ast			*add_redirect_node(t_ast *parent, t_ast *child);
t_ast			*add_cmd_node(t_ast *parent, t_ast *child);
t_ast			*add_ast_node(t_ast *parent, t_ast *child);
t_ast			*make_ast(t_token_list *list);
t_ast			*make_ast_node(t_token_list *list);
int env_sub(t_token_list *list, t_env *env);


#endif
