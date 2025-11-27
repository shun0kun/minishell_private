#include "private.h"

void	execute_and(t_node *node, int *exit_status)
{
	execute_ast(node->lhs, exit_status);
	if (*exit_status == 0)
	{
		execute_ast(node->rhs, exit_status);
	}
}

void	execute_or(t_node *node, int *exit_status)
{
	execute_ast(node->lhs, exit_status);
	if (*exit_status != 0)
	{
		execute_ast(node->rhs, exit_status);
	}
}

void	execute_ast(t_node *node, int *exit_status)
{
	if (!node)
		return ;
	if (node->kind == ND_AND)
	{
		execute_and(node, exit_status);
	}
	else if (node->kind == ND_OR)
	{
		execute_or(node, exit_status);
	}
	else
	{
		execute_pipeline(node, exit_status);
	}
}
