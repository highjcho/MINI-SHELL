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
	t_env_node h_node;
} t_env;

enum e_token_type
{
	WORD,
	REDIRECT,
	PIPELINE,
	PIPE,
};

enum e_node_type
{
	CMD,
	REDIRECT,
	PIPELINE,
	PIPE,
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

typedef struct s_ast
{
	struct s_ast 	*left;
	struct s_ast 	*right;
		char 			*data;
	enum e_node_type type;
}	t_ast;

#endif