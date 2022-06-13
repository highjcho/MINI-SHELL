/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:11:33 by hyunjcho          #+#    #+#             */
/*   Updated: 2022/06/09 11:11:34 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/init.h"

static int	init_add_env(t_env *env, char **export)
{
	t_env_node	*prev;
	t_env_node	*new;

	new = malloc(sizeof(t_env_node));
	if (!new)
	{
		double_free(export);
		return (FALSE);
	}
	prev = &(env->h_node);
	while (prev->next)
		prev = prev->next;
	prev->next = new;
	new->key = export[0];
	new->value = export[1];
	free(export);
	new->next = NULL;
	if (!ft_strcmp(export[0], "PWD"))
		env->pwd = new;
	if (!ft_strcmp(export[0], "OLDPWD"))
		env->old_pwd = new;
	return (TRUE);
}

static int	set_env(t_env *env, char **envp)
{
	char		**export;
	int			i;

	i = -1;
	while (envp[++i])
	{
		export = ft_split(envp[i], '=');
		if (!export)
			return (FALSE);
		if (!init_add_env(env, export))
		{
			free_env(env);
			return (FALSE);
		}
	}
	export = ft_split("?=0", '=');
	if (!export)
		return (FALSE);
	if (!add_env(env, export))
	{
		free_env(env);
		return (FALSE);
	}
	env->exit_code = get_env_node(env, "?");
	return (TRUE);
}

int	init_env(t_env *env, char **envp)
{
	env->h_node.next = NULL;
	env->pwd = NULL;
	env->old_pwd = NULL;
	env->exit_code = NULL;
	env->path = NULL;
	if (!set_env(env, envp))
		return (FAIL);
	return (SUCCESS);
}
