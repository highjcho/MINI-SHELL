/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonkim <jonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:37 by jonkim            #+#    #+#             */
/*   Updated: 2022/06/13 16:42:31 by jonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

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
		sub = ft_strdup("");
	sub = ft_strdup(sub);
	if (!ret)
		return (NULL);
	while (str[++i])
	{
		if (i < pos2 && i >= pos1)
			while (sub[j])
				ret[idx++] = sub[j++];
		else
			ret[idx++] = str[i];
	}
	free(sub);
	free(str);
	return (ret);
}

char	*substitution(char *str, int *pos1, int pos2, t_env *env)
{
	int	i;
	int	tmp;
	char *key;
	char *sub;

	i = *pos1 - 1;
	key = NULL;
	while (str[++i])
	{
		if (i >= pos2)
			break;
		if (str[i] == '$') // str[i] == '$'
		{
			tmp = i + 1;
			if ((tmp <= pos2) && str[tmp] == '?') // 영문으로 시작하지 않고  _ 로 시작하지도 않을때는
			{
				str = ret_sub(str, get_env_value(env, "?"), i, tmp + 1);
				break; 
			}
			if ((tmp <= pos2) && str[tmp] && str[tmp] != '_' && !ft_isalpha(str[tmp]) && str[tmp] != '$') // 영문으로 시작하지 않고  _ 로 시작하지도 않을때는
			{
				if ((str[tmp] != '\'' && str[tmp] != '\"') || !find_c(str + tmp + 1,str[tmp]))// 바로뒤가 따옴표가 아니거나 , 따옴표 짝이 안맞을때 
				str = ret_sub(str, NULL, i, tmp + 1);
				break; 
			}
			while (tmp <= pos2 && str[tmp] && (ft_isalnum(str[tmp]) || str[tmp] == '_'))  // $fewl
				tmp++;
			key = ft_substr(str, i + 1, tmp - i - 1);
			sub = get_env_value(env, key);
			*pos1 += ft_strlen(sub) - 1;
			free(key);
			return (ret_sub(str, sub, i, tmp));// $ 위치에서부터 치환 str[tmp -1] 위치까지 sub로 치환
		}
	}
	return (str);
}


char	*quote_trim(char *str, int pos1, int pos2) // quotation 2개를 지워주는 함수.
{
	char	*ret;
	int		i;
	int		index;

	i = -1;
	index = 0;
	ret = malloc(ft_strlen(str) - 1);
	if(!str)
		return (NULL);
	while (str[++i])
	{
		if (i != pos1 && i != pos2)// quote 위치가 아니라면
		{
			ret[index] = str[i];
			index++;
		}
	}
	ret[index] = 0;
	return (ret);
}

char	*double_quote_trim(char *str, t_env *env, int *pos1, int pos2) // quotation 2개를 지워주고 환경변수 치환하는 함수.
{
	int	i;
	int	tmp;

	str = quote_trim(str, *pos1, pos2);
	tmp = ft_strlen(str);
	i = *pos1 - 1;
	while (str[++i] && i < pos2 - 2)
	{
		if (str[i] == '$')
		{
			str = substitution(str, &i, pos2 - 2, env);
			pos2 -= tmp - ft_strlen(str);
		}
	}
	*pos1 = i - 1;
	return (str);
}


char	*env_check(char *str, t_env *env)
{
	char	*ret;
	int		i;
	int		tmp;

	ret = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			tmp = i + 1;
			while (str[tmp] && str[tmp] != '\'') // 짝을 찾을때까지 밀어준다. 
				tmp++;
			if (str[tmp] == '\'') // 짝이 있으면
			{
				str = quote_trim(str, i, tmp); // 지워준다.
				i = tmp - 2;
			}
		}
		else if (str[i] == '\"')
		{
			tmp = i + 1;
			while (str[tmp] && str[tmp] != '\"') // 짝을 찾을때까지 밀어준다. 
				tmp++;
			if (str[tmp] == '\"') // 짝이 있으면
				str = double_quote_trim(str, env, &i, tmp); //quote_sub(); // 환경변수 치환도 해준다. , 지워주는 로직도 추가
		}
		else if (str[i] == '$')
			str = substitution(str, &i, ft_strlen(str), env);
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
			cur->token.str = env_check(cur->token.str, env);
		cur = cur->next;
	}
	return (0);
}
