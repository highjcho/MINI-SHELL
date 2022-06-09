/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunjcho <hyunjcho@student.42seoul.>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:10:04 by hyunjcho          #+#    #+#             */
/*   Updated: 2022/06/09 11:10:06 by hyunjcho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static int	empty_value(char	**export)
{
	export[1] = ft_strdup("");
	{
		free(export[0]);
		free(export);
		return (FALSE);
	}
	return (TRUE);
}

static int	check_key(char *key)
{
	int	i;
	
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (FALSE);
	i = 0;
	while (key[++i])
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (FALSE);
	return (TRUE);
}

int	mini_export(t_env *env, char **cmd)
{
	char	**export;
	int		i;

	i = 0;
	while (cmd[++i])
	{
		if (!find_c(cmd[i], '='))
			continue ;
		export = ft_split(cmd[i], '=');
		if (!export)
			return (FAIL);
		if (!check_key(export[0]))
		{
			printf("minishell: export '%s': not a valid identifier\n", cmd[1]);
			double_free(export);
			continue ;
		}
		if (export[1] == NULL)
			if (!empty_value(export))
				return (FAIL);
		if (!add_env(env, export))
			return (FAIL);
	}
	return (SUCCESS);
}
