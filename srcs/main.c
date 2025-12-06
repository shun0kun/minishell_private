#include "minishell.h"

void	free_tokens(t_token *token)
{
	t_token	*cur;
	t_token	*next;

	cur = token;
	while (cur)
	{
		next = cur->next;
		free(cur->value);
		free(cur);
		cur = next;
	}
}

void	free_ast(t_node *node)
{
	if (node->lhs)
		free_ast(node->lhs);
	if (node->rhs)
		free_ast(node->rhs);
	if (!node->lhs && !node->rhs)
		free(node);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	t_token	*token;
	t_node	*node;

	init_shell(&shell, envp);
	while (1)
	{
		line = readline("$ ");
		if (!line)
		{
			shell.exit_status = 1;
			continue ;
		}
		token = tokenize(line, &shell);
		if (validate_tokens(token) == 0)
		{
			node = list(&token);
			execute_ast(node, &shell);
		}
		free_tokens(token);
		free_ast(node);
		free(line);
	}
	cleanup_shell(&shell);
	return (0);
}
