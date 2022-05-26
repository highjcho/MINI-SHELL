#include "../../includes/parse.h"

t_ast *add_pl_node(t_ast *parent, t_ast *child)
{
	if (child->type == REDIRECT)
	{
		if (parent->left == NULL)
			parent->left = child;
		else
			add_ast_node(parent->left, child);
		return (parent);
	}
	else if (child->type == CMD)
	{
		if (parent->left == NULL)
			parent->left = child;
		else if (parent->right == NULL)
			parent->right = child;
		else
			add_ast_node(parent->right, child);
		return (parent);
	}
	else 
	{
		if (child->left == NULL)
			child->left = parent;
		else
			child->right = parent;
		return (child);
	}
}

t_ast *add_pipe_node(t_ast *parent, t_ast *child)
{
	if (child->type == REDIRECT || child->type == CMD)
	{
		if (parent->right == NULL)
		{
			parent->right = make_ast_node(NULL);
			add_ast_node(parent, child);
		}
		else
			add_ast_node(parent->right, child);
	}
	else
	{
		if (parent->right == NULL)
			parent->right = child;
		else
			add_ast_node(parent->right, child);
	}
			return (parent);
}

t_ast *add_redirect_node(t_ast *parent, t_ast *child)
{
	if (child->type == REDIRECT)
	{
		if (parent->right == NULL)
			parent->right = child;
		else
			add_ast_node(parent->right, child);
	}
	else
	{
		if (parent->left == NULL)
			parent->left = child;
		else
			add_ast_node(parent->right, child);
	}
			return (parent);
}

t_ast *add_cmd_node(t_ast *parent, t_ast *child)
{
	if (parent->right == NULL)
		parent->right = child;
	else
		add_ast_node(parent->right, child);
	return (parent);
}