#include "minishell.h"

void	print_tokens(t_token *token)
{
	char *arr[] = {"TK_WORD", "TK_REDIR", "TK_PIPE", "TK_LPAREN", "TK_RPAREN", "TK_AND", "TK_OR", "TK_EOF", NULL};

	if (!token)
	{
		printf("つくれてない\n");
		return ;
	}
	while (token->kind != TK_EOF)
	{
		printf("%-20s[%s]\n", arr[token->kind], token->value);
		token = token->next;
	}
	printf("%s\n", arr[token->kind]);
}

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

int	is_same_str(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (s1[i] == s2[i]);
}

// void	check_node(t_node *node)
// {
// 	char	*arr[] = {"ND_CMD", "ND_PIPE", "ND_AND", "ND_OR"};
// 	int		i;
// 	t_node	*nodee;

// 	printf("%s\n", arr[node->kind]);
// 	nodee = node->rhs;
// 	i = 0;
// 	while (nodee->cmd->argv[i])
// 	{
// 		printf("%s, ", nodee->cmd->argv[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	t_redir	*cur = nodee->cmd->redir;
// 	while (cur)
// 	{
// 		printf("(%s)-", cur->filename);
// 		cur = cur->next;
// 	}
// 	printf("\n");
// }

int	main(void)
{
	char	*line;
	t_token	*token;
	t_node	*node;

	while (1)
	{
		line = readline("$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (is_same_str(line, "clear"))
		{
			write(1, "\033[2J\033[H", 7);
			free(line);
		}
		else if (is_same_str(line, "exit"))
		{
			exit(0);
		}
		else
		{	
			token = tokenize(line);
			if (validate_tokens(token))
			{
				node = list(&token);
				print_ast(node);
			}
			free_tokens(token);
			//free_node
			free(line);
		}
	}
	return (0);
}
