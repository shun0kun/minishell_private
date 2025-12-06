#include "private.h"

void	execute_and(t_node *node, int *exit_status, t_env *env)
{
	execute_ast(node->lhs, exit_status, env);
	if (*exit_status == 0)
	{
		execute_ast(node->rhs, exit_status, env);
	}
}

void	execute_or(t_node *node, int *exit_status, t_env *env)
{
	execute_ast(node->lhs, exit_status, env);
	if (*exit_status != 0)
	{
		execute_ast(node->rhs, exit_status, env);
	}
}

void	execute_ast(t_node *node, int *exit_status, t_env *env)
{
	if (!node)
		return ;
	if (node->kind == ND_AND)
	{
		execute_and(node, exit_status, env);
	}
	else if (node->kind == ND_OR)
	{
		execute_or(node, exit_status, env);
	}
	else
	{
		execute_pipeline(node, exit_status, env);
	}
}
