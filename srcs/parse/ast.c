/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonkim <jonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:55 by jonkim            #+#    #+#             */
/*   Updated: 2022/06/01 15:53:07 by jonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

t_ast	*make_ast_node(t_token_list *list)// ast node들을 생성하는 함수
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		return (NULL);
	if (!list) //매개 변수로 NULL 이 들어왔을때는 PIPELINE node를 생성
		node->type = PIPELINE;
	else
	{
		node->data = list->token.str;
		node->type = list->token.type;
	}
	return (node);
}

t_ast	*add_ast_node(t_ast *parent, t_ast *child)// parent 에 child 를 추가할때 parent 의 type을 보고 분기한다.
{
	t_ast	*root;

	if (!parent || !child)
		return (NULL);
	if (parent->type == PIPELINE)
		root = add_pl_node(parent, child);
	else if (parent->type == PIPE)
		root = add_pipe_node(parent, child);
	else if (parent->type == REDIRECT)
		root = add_redirect_node(parent, child);
	else if (parent->type == WORD)
		root = add_cmd_node(parent, child);
	else
		root = NULL;
	return (root);
}

t_ast	*make_ast(t_token_list *list) //token_list 를 순회하면서 ast를 생성하는 함수
{
	t_token_list	*cur;
	t_ast			*root;
	t_ast			*node;

	root = make_ast_node(NULL); // 처음 root 는 PIPELINE
	cur = list ->next;// 연결리스트 head 는 비어 있으므로 한칸 밀어준다.
	while (cur)
	{
		node = make_ast_node(cur); // token에 맞는 node를 생성
		if (!node)
			return (NULL);
		root = add_ast_node(root, node); // root 에 node를 추가한다. root를 갱신
		cur = cur -> next;
	}
	return (root);
}
