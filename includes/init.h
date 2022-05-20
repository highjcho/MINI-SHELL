#ifndef INIT_H
# define INIT_H

# include "minishell.h"

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env
{
	t_env_node h_node;
} t_env;

int	init_env(t_env *env, char **envp);

# endif