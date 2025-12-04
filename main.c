#include "minishell.h"

#define rep(i,n) for (int i = 0; i < (n); ++i)

void print_ast(t_node *node)
{
    static const char	*nds[] = {"ND_PIPELINE","ND_AND","ND_OR"};
    static const int width = 3;
    static int depth = 1;
    static int is_right = 1;
    static long long mask=0;

    mask = (mask & ~(1<<depth)) | ((!is_right) << depth);
    if(depth >= 3)for(int i=2;i<depth;i++){
        printf("%s",(mask & 1<<i)?"│":" ");
        rep(i,width)printf(" ");
    }
    if(depth>=2){
        printf("%s",is_right?"└":"├");
        rep(i,width)printf("─");
        printf(" ");
    }
	printf("%s\n",nds[node->kind]);
	if(node->kind == ND_PIPELINE)
		return;
	is_right = 0;
	depth++;
	print_ast(node->lhs);
	is_right = 1;
	print_ast(node->rhs);
	depth--;
}

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

int	main(void)
{
	char	*line;
	t_token	*token;
	t_node	*node;
	t_env	*env;
	int		exit_status;

	env = inherit_env();
	while (1)
	{
		line = readline("$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		if (ft_strcmp(line, "clear") == 0)
		{
			write(1, "\033[2J\033[H", 7);
			free(line);
		}
		else if (ft_strcmp(line, "exit") == 0)
		{
			exit(0);
		}
		else if (ft_strcmp(line, "env") == 0)
		{
			print_env(env);
		}
		else
		{
			token = tokenize(line, exit_status);
			// print_tokens(token);
			if (validate_tokens(token))
			{
				node = list(&token);
				// print_ast(node);
				execute_ast(node, &exit_status, env);
			}
			free_tokens(token);
			//free_node
			free(line);
		}
	}
	return (0);
}
