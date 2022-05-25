#ifndef PARSE_H
# define PARSE_H

# include "minishell.h"

char			**tokenize(char *str);
t_token_list	*make_token_list(char **tokens);

#endif
