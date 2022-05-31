#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

int			add_env(t_env *env, char **export);
t_env_node	*get_key_node(t_env *env, char *key);
void		free_env_node(t_env_node *node);
void		free_env(t_env *env);
void		double_free(char **str);
void		print_art(void);

#endif
