#include "../../includes/minishell.h"

int	quote(char *str, int *i, char c)
{
	while (str[(*i)])
	{
		if (str[*i] == 0)
			return (-1);
		if (str[*i] == c)
			break;
		(*i)++;
	}
	return (0);
}

int	word(char *str, int *i)
{
	while (str[(*i)])
	{
		if (str[*i] == 0)
			return (-1);
		if (str[*i] == ' ')
			break;
		(*i)++;
	}
	return (0);
}

int	token_count(char *str)
{
	int	ret;
	int	i;

	ret = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == "'" || str[i] == '"')
		{
			if (quote(str, &i, str[i]) == -1);
				return (-1);
		}
		else if (str[i] != ' ')
			if (word(str, &i) == -1)
				return (-1);
		while (str[i] == ' ')
			i++;
		ret++;
	}
	return (ret);
}

char	**tokenize(char *str)
{
	char	**tokens;
	int		i;

	i = -1;
	if (token_count(str) == -1)
		return (NULL);
	tokens = malloc((sizeof(char*) * token_count(str)) + 1);
	if (!tokens)
		return (NULL);
	// while (str[++i])
	// {
	// 	if (str[i] == "'" || str[i] == '"')
	// 	{
	// 		if (quote(str, &i, str[i]) == -1);
	// 			return (-1);
	// 	}
	// 	else if (str[i] != ' ')
	// 		if (word(str, &i) == -1)
	// 			return (-1);
	// 	//길이 재서 문자열 만들고 붙여주기 
	// 	while (str[i] == ' ')
	// 		i++;
	// }
	//문자열중에 하나라도 NULL	 다 프리처리해주고 
	//리턴줄 
}
