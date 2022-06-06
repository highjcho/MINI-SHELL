/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonkim <jonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:37 by jonkim            #+#    #+#             */
/*   Updated: 2022/06/01 18:47:38 by jonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

char	*quote_trim(char *str, int pos1, int pos2)
{
	char	*ret;
	int		i;
	int		tmp;

	i = -1;
	tmp = 0;
	ret = malloc(ft_strlen(str) - 1);
	if (!ret)
		return (NULL);
	while (str[++i])
	{
		if (i != pos1 && i != pos2)
		{
			ret[tmp] = str[i];
			tmp++;
		}
	}
	ret[tmp] = 0;
	free(str);
	return (ret);
}

char	*quote_check(char *str)
{
	int	i;
	int	tmp;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp = i;
			while (str[++tmp])
			{
				if (str[tmp] == str[i])
				{
					str = quote_trim(str, i, tmp);
					i = -1;
				}
			}
		}
	}
	return (str);
}

char	*ret_sub(char *str, char *sub, int pos1, int pos2)
{
	char	*ret;
	int		i;
	int		j;
	int		idx;

	i = -1;
	j = 0;
	idx = 0;
	ret = ft_calloc(ft_strlen(str) - pos2 + pos1 + ft_strlen(sub) + 1, 1);
	if (!sub)
		sub = ft_strdup(""); // free 생각
	if (!ret)
		return (NULL);
	while (str[++i])
	{
		if (i <= pos2 && i >= pos1)
		{
			while (sub[j])
				ret[idx++] = sub[j++];
		}
		else
			ret[idx++] = str[i];
	}
	free(str);
	return (ret);
}

char	*substitution(char *str, int pos, t_env *env)
{
	int		tmp;
	char	*sub;

	tmp = pos + 1;
	pos++;
	if (str[pos] == '?')
	pos++;
	while (ft_isalnum(str[pos]) || str[pos] == '_')
		pos++;
	sub = get_env_value(env, ft_substr(str, tmp, pos - tmp));
	return (ret_sub(str, sub, tmp - 1, pos - 1));
}

char	*env_check(char *str, t_env *env)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			tmp = i;
			while (str[++tmp])
			{
				if (str[tmp] == str[i])
					i = tmp;
			}
		}
		if (str[i] == '$')
			return (substitution(str, i, env));
	}
	return (str);
}

int	env_sub(t_token_list *list, t_env *env)
{
	t_token_list	*cur;

	cur = list;
	while (cur)
	{
		if (cur->token.type == WORD && cur->token.str)
		{
			cur->token.str = env_check(cur->token.str, env);
			cur->token.str = quote_check(cur->token.str);
		}
		cur = cur->next;
	}
	return (0);
}
