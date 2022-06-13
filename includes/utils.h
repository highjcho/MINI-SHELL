/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:41:24 by hyunjcho          #+#    #+#             */
/*   Updated: 2022/06/09 15:41:25 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

int			add_env(t_env *env, char **export);
char		*get_env_value(t_env *env, char *key);
t_env_node	*get_env_node(t_env *env, char *key);
int			update_exit_code(t_env *env, char *exit_code);
void		double_free(char **str);
int			find_c(char *s, char c);
int			check_key(char *key);
int			is_long(char *s);
long long	ft_atol(char *s);
void		free_env_node(t_env_node *node);
void		free_env(t_env *env);
void		free_ast(t_ast *node);
void		all_free(t_info *info);
void		setechoctl(int flag);
int			main_init(char *line, t_info *info);
int			set_init(t_env *env, char **envp, char **av);
char		*get_next_line(int fd);
void		print_art(void);

# define BUFFER_SIZE 4096

#endif
