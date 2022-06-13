/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonkim <jonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:32:35 by jonkim            #+#    #+#             */
/*   Updated: 2022/06/09 19:30:44 by jonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	main_init(char *line, t_info *info)
{
	ft_memset(info, 0, sizeof(t_info));
	info->list = make_token_list(tokenize(line));
	env_sub(info->list, g_env);
	info->ast = make_ast(info->list);
	if (syntax_check(info->ast) == FAIL)
	{
		update_exit_code(g_env, ft_strdup("258"));
		return (FAIL);
	}
	ast_merge(info->ast);
	info->pl = pl_list(info->ast);
	return (SUCCESS);
}

int	set_init(t_env *env, char **envp, char **av)
{
	(void)av;
	init_env(env, envp);
	g_env = env;
	signal_init();
	setechoctl(1);
	return (SUCCESS);
}
