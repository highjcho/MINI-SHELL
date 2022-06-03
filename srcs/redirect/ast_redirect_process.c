#include "../../includes/redirect.h"

void redirect_in(t_ast *pipeline, t_ast *node)
{
	if (!ft_strncmp("<<", node->data, 2))
	{
		/*heardoc*/
	}
	else if (!ft_strncmp("<",node->data, 1))
	{
		if (pipeline->in_fd > 2)
			close(pipeline->in_fd);
		pipeline->in_fd = open(node->file_name,O_RDONLY);
	}
	else if (!ft_strncmp("<>", node->data, 2))
		pipeline->in_fd = -1;
	if (node->right)
		redirect_in(pipeline, node->right);
}


void redirect_out(t_ast *pipeline, t_ast *node)
{
	if (!ft_strncmp(">",node->data, ft_strlen(node->data)))
	{
		if (pipeline->out_fd > 2)
			close(pipeline->out_fd);
		pipeline->out_fd = open(node->file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	}
	else if (!ft_strncmp(">>", node->data, ft_strlen(node->data)))
	{
		if (pipeline->out_fd > 2)
			close(pipeline->out_fd);
		pipeline->out_fd = open(node->file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	}
	else if (!ft_strncmp("><", node->data, ft_strlen(node->data)))
		pipeline->in_fd = -1;
	if (node->right)
		redirect_out(pipeline, node->right);
}



void ast_redirect_process(t_ast *ast)
{
	if (ast->type == PIPELINE)
	{
		if (ast->left)
		{
			redirect_in(ast, ast->left);
			redirect_out(ast, ast->left);
		}
	}
	if (ast->left)
		ast_redirect_process(ast->left);
	if (ast->right)
		ast_redirect_process(ast->right);
}