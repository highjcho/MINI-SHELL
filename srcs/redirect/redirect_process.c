/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonkim <jonkim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 12:42:10 by jonkim            #+#    #+#             */
/*   Updated: 2022/06/09 12:42:37 by jonkim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/redirect.h"

void	redirect_in(t_ast *pipeline, t_ast *node)
{
	if (!ft_strcmp("<<", node->data))
	{
		if (pipeline->in_fd != STDIN_FILENO)
			close(pipeline->in_fd);
		here_doc(pipeline, node);
	}
	else if (!ft_strcmp("<", node->data))
	{
		if (pipeline->in_fd != STDIN_FILENO)
			close(pipeline->in_fd);
		pipeline->in_fd = open(node->file_name, O_RDONLY);
	}
}

void	redirect_out(t_ast *pipeline, t_ast *node)
{
	if (!ft_strncmp(">", node->data, ft_strlen(node->data)))
	{
		if (pipeline->out_fd > STDOUT_FILENO)
			close(pipeline->out_fd);
		pipeline->out_fd = open(node->file_name, O_RDWR \
		| O_CREAT | O_TRUNC, 0644);
	}
	else if (!ft_strncmp(">>", node->data, ft_strlen(node->data)))
	{
		if (pipeline->out_fd > STDOUT_FILENO)
			close(pipeline->out_fd);
		pipeline->out_fd = open(node->file_name, O_RDWR | \
		O_CREAT | O_APPEND, 0644);
	}
}

void	redirect_process(t_ast *ast, t_ast *node)
{
	if (node -> data && node->data[0] == '<')
		redirect_in(ast, node);
	else if (node -> data && node->data[0] == '>')
		redirect_out(ast, node);
	if (node->right)
		redirect_process(ast, node->right);
}

void	ast_redirect_process(t_ast *ast)
{
	if (ast->type == PIPELINE)
	{
		if (ast->left)
			redirect_process(ast, ast->left);
	}
}
