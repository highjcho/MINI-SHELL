#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void 		print_art(void);
t_env_node	*get_key_node(t_env *env, char *key);
void	double_free(char **str);


#endif
