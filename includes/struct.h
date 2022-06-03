#ifndef STRUCT_H
# define STRUCT_H

# include "minishell.h"

typedef struct s_env_node
{
	char				**export;
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env
{
	t_env_node	h_node;
	t_env_node	*pwd; // 필요한 게 맞는 지 사실 아직 감이 잘 안옴;
	t_env_node	*old_pwd;
	char		**path;
} t_env;

enum e_token_type
{
	WORD,
	REDIRECT,
	PIPELINE,
	PIPE,
};

typedef struct s_token
{
	char				*str;
	enum e_token_type	type;
}	t_token;

typedef struct s_token_list
{
	struct s_token_list	*next;
	t_token				token;
}	t_token_list;

typedef struct s_cmd
{
	char	*path;
	char	**cmd; // 트리에서 돌기
	int		in_fd;
	int		out_fd;
}	t_cmd;

typedef struct s_ast
{
	struct s_ast	*left;
	struct s_ast	*right;
	char			*data;
	int				ac;
	char			*path;
	char			**av;
	char			*file_name;
	int				in_fd;
	int				out_fd;
	enum e_token_type	type;
}	t_ast;

typedef struct s_pl_list
{
	struct s_ast		*pipeline;
	struct s_pl_list	*next;
}	t_pl_list;

#endif