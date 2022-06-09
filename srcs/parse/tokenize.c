/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonkim <jonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:50:16 by jonkim            #+#    #+#             */
/*   Updated: 2022/06/09 12:53:59 by jonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

void	quote(char *str, int *i, char c)
{
	int	tmp;

	tmp = *i;
	while (str[++(*i)])
	{
		if (str[*i] == c)
		{
			(*i)++;
			return ;
		}
	}
	*i = tmp + 1;
}

void	word(char *str, int *i)
{
	if (!str[*i])
		return ;
	while (str[(*i)])
	{
		if (str[*i] == ' ' || str[*i] == '|' || \
		str[*i] == '>' || str[*i] == '<')
			return ;
		if (str[*i] == '\'' || str[*i] == '\"')
			quote(str, i, str[*i]);
		(*i)++;
	}
}

void	redirection(char *str, int *i)
{
	if (str[(*i) + 1] == str[*i])
		(*i)++;
	(*i)++;
}

int	token_count(char *str)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			ret++;
			i++;
		}
		if (str[i] == '<' || str[i] == '>')
			redirection(str, &i);
		if (str[i] == '\'' || str[i] == '\"')
			quote(str, &i, str[i]);
		if (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' && \
		str[i] != '|' && str[i] != '>' && str[i] != '<')
			word(str, &i);
		while (str[i] == ' ')
			i++;
		ret++;
	}
	return (ret);
}

char	**make_token(char *str, char **tokens)
{
	int	i;
	int	j;
	int	tmp;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		tmp = i;
		if (str[i] == '|')
		{
			tokens[j++] = ft_strdup("|");
			i++;
			tmp++;
		}
		if (str[i] == '<' || str[i] == '>')
		{
			redirection(str, &i);
			tokens[j++] = ft_substr(str, tmp, i - tmp);
			tmp = i;
		}
		if (str[i] == '\'' || str[i] == '\"')
			quote(str, &i, str[i]);
		if (str[i] != ' ' && str[i] != '\'' && str[i] != '\"' \
		&& str[i] != '|' && str[i] != '>' && str[i] != '<')
			word(str, &i);
		if (i != tmp)
		{
			tokens[j++] = ft_substr(str, tmp, i - tmp);
	//		if (tokens[j - 1] == NULL) error 시에 배열 해제 필요 
		}
	}
	tokens[token_count(str)] = 0;
	return (tokens);
}

char	**tokenize(char *str)
{
	char	**tokens;

	if (token_count(str) == 0)
		return (NULL);
	tokens = malloc((sizeof(char *) * (token_count(str) + 1)));
	if (!tokens)
		return (NULL);
	tokens = make_token(str, tokens);
	return (tokens);
}
