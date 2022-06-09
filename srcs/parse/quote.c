/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonkim <jonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:46:25 by jonkim            #+#    #+#             */
/*   Updated: 2022/06/09 12:47:39 by jonkim           ###   ########.fr       */
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
