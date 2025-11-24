#include "../minishell.h"
#include "private.h"

t_node	*new_node(t_node_kind kind, t_node *lhs, t_node *rhs) //cmd以外用
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->kind = kind;
	node->lhs = lhs;
	node->rhs = rhs;
	return (node);
}

t_node	*new_node_cmd(t_cmd *cmd) //cmd用
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->kind = ND_CMD;
	node->cmd = cmd;
	node->lhs = NULL;
	node->rhs = NULL;
	return (node);
}

t_node	*pipeline(t_token **token)
{
	t_node	*node;

	node = new_node_cmd(consume_cmd(token));
	while (1)
	{
		if (consume(TK_PIPE, token))
			node = new_node(ND_PIPE, node, pipeline(token));
		else
			return (node);
	}
}

t_node	*paren(t_token **token)
{
	t_node	*node;

	if (consume(TK_LPAREN, token))
	{
		node = list(token);
		consume(TK_RPAREN, token);
	}
	else
		node = pipeline(token);
	return (node);
}

t_node	*list(t_token **token)
{
	t_node	*node;

	node = paren(token);
	while (1)
	{
		if (consume(TK_AND, token))
			node = new_node(ND_AND, node, paren(token));
		else if (consume(TK_OR, token))
			node = new_node(ND_OR, node, paren(token));
		else
			return (node);
	}
}
