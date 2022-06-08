#ifndef REDIRECT_H
# define REDIRECT_H

# include "minishell.h"

# define BUFFER_SIZE 1024

int		dup_fd(int from_fd, int to_fd);
void	ast_redirect_process(t_ast *ast);

#endif
