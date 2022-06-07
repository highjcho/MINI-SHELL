#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

int		add_env(t_env *env, char **export);
char	*get_env_value(t_env *env, char *key);
void	free_env_node(t_env_node *node);
void	free_env(t_env *env);
void	double_free(char **str);
void	print_art(void);
void	ast_free(t_ast *node);
int		find_c(char *s, char c);


#endif
