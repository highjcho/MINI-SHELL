#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_env_node
{
	char				*key;
	char				*value;
	int					e_flag;
	char				**export;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env
{
	t_env_node	h_node;
	t_env_node	*pwd; // 필요한 게 맞는 지 사실 아직 감이 잘 안옴;
	t_env_node	*old_pwd;
} t_env;

enum e_token_type
{
	WORD,
	PIPE,
	REDIRECT
};

typedef struct s_token
{
	char				*str;
	enum e_token_type 	type;
}	t_token;

typedef struct s_token_list
{
	struct s_token_list *next;
	t_token token;
}	t_token_list;

typedef struct s_cmd
{
	char	*path;
	char	**cmd;
}	t_cmd;

#endif