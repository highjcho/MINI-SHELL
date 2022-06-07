/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntaxcheck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonkim <jonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:49:58 by jonkim            #+#    #+#             */
/*   Updated: 2022/06/07 15:40:52 by jonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parse.h"

int recur_syntax_check(t_ast *ast)
{
	if (!ast || ast->type == WORD)
		return (SUCCESS);
	if (ast->type == PIPE)
		if (ast->left == NULL && ast->right ==NULL)
			return (FAIL);
	if (ast->type == REDIRECT)
		if (ast->left == NULL)
			return (FAIL);
	if (ast->type == PIPELINE)
		if (ast->left == NULL && ast ->right == NULL)
			return (FAIL);
	if (recur_syntax_check(ast->left))
		return (FAIL);
	else if (recur_syntax_check(ast->right))
		return (FAIL);
	else 
		return (SUCCESS);
}

int syntax_check(t_ast *ast)
{
	if (ast->type == PIPE && ast->right == NULL)
		return (FAIL);
	if (recur_syntax_check(ast->left))
		return (FAIL);
	else if (recur_syntax_check(ast->right))
		return (FAIL);
	else
		return (SUCCESS);
}
