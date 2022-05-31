#include "../../includes/parse.h"

char *quote_trim(char *str, int pos1, int pos2)
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
	str = NULL;
	return (ret);
}

int quote_check(char *str)
{
	int	i;
	int tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'')
		{
			tmp = i;
			while (str[++tmp])
			{
				if (str[tmp] == str[i])
				str = quote_trim(str, i, tmp);
			}
		}
		else if (str[i] == '\"')
		{
			tmp = i;
			while (str[++tmp])
			{
				if (str[tmp] == str[i])
				str = quote_trim(str, i, tmp);
			}
		}
	}
	return (0);
}

char	*substitution(char *str, int pos, t_env *env)
{
	int tmp;
	char *sub;
	char *ret;

	tmp = pos + 1;
	while (ft_isalnum(str[pos]) || str[pos] == '_')
		pos++;
	sub = get_key_node(env, ft_substr(str, tmp, pos - tmp))->value;
	ret = ft_calloc(ft_strlen(sub) + ft_strlen(str) - pos + tmp, sizeof(char));
	printf("env = %s ", sub);
	// free (str);	
	// return (sub);
	return (str);
}

int env_check(char *str, t_env *env)
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
			str = substitution(str, i, env);
	}
	return (0);
}

int env_sub(t_token_list *list, t_env *env)
{
	t_token_list *cur;

	cur = list;
	while (cur)
	{
		if (cur->token.type == WORD && cur->token.str)
		{
			env_check(cur->token.str, env);
			quote_check(cur->token.str);	
		}
		cur = cur->next;
	}
	return (0);
}