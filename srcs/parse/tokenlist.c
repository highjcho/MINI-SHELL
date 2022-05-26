#include "../../includes/parse.h"

t_token_list *new_token_node(char *tok)
{
	t_token_list	*new_token;
	int	toklen;

	new_token = malloc(sizeof(t_token_list));
	if (!new_token)
		return (NULL);
	new_token->token.str = tok;
	toklen = ft_strlen(tok); 
	if (!ft_strncmp(tok, "<", toklen) || !ft_strncmp(tok, "<<", toklen)\
	 ||!ft_strncmp(tok, ">>", toklen) || !ft_strncmp(tok, ">", toklen))
		new_token->token.type = REDIRECT;
	else if (!ft_strncmp(tok, "|", toklen))
	{
		new_token->token.str = ft_strdup("|");
		new_token->token.type = PIPE;
	}
	else
		new_token->token.type = WORD;
	new_token->next=NULL;
	return (new_token);
}

t_token_list *make_token_list(char **tokens)
{
	int	i;
	t_token_list	*start;
	t_token_list	*cur;
	t_token_list	*new_token;

	start = ft_calloc(1, sizeof(t_token_list));
	cur = start;
	i = -1;
	while (tokens[++i])
	{
		new_token = new_token_node(tokens[i]);
		cur->next = new_token;
		cur = cur->next;
	}
	return (start);
}