#include "header.h"

void	print_tokens(t_token *token)
{
	char *arr[] = {"TOK_NO", "TOK_WORD", "TOK_RED", "TOK_PIPE", "TOK_ANDOR", "TOK_KAKKOO", "TOK_KAKKOC", "TOK_EOF", "\0"};

	if (!token)
	{
		printf("つくれてない\n");
		return ;
	}
	while (token->type != TOK_EOF)
	{
		printf("%-20s[%s]\n", arr[token->type], token->value);
		token = token->next;
	}
	printf("%s\n", arr[token->type]);
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

int	main(void)
{
	char	*line;
	t_token	*token;

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
			continue ;
		}
		token = tokenize(line);
		print_tokens(token);
		free_tokens(token);
		free(line);
	}
	return (0);
}
