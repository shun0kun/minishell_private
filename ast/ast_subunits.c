#include "../minishell.h"
#include "private.h"

void	free_command(t_pipeline *pipeline, t_redir *redir)
{
	size_t	i;
	t_redir	*cur;
	t_redir	*next;

	if (!pipeline)
		return ;
	i = 0;
	if (pipeline->argv)
	{
		while (pipeline->argv[i])
		{
			free(pipeline->argv[i]);
			i++;
		}
	}
	cur = redir;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(pipeline);
}

t_redir	*redir_add(t_redir *redir, t_token *token)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	redir->next = new_redir;
	if (token->value[0] == '>' && token->value[1] == '>')
		new_redir->kind = APPEND;
	else if (token->value[0] == '<' && token->value[1] == '<')
		new_redir->kind = HEREDOC;
	else if (token->value[0] == '>')
		new_redir->kind = OUT;
	else if (token->value[0] == '<')
		new_redir->kind = IN;
	new_redir->filename = (token->next)->value;
	new_redir->next = NULL;
	return (new_redir);
}

t_pipeline	*get_command(t_token **token, int cmd_len, int redir_count)
{
	t_pipeline	*pipeline;
	t_redir		head;
	t_redir		*redir;
	size_t		i;

	pipeline = malloc(sizeof(t_pipeline *));
	if (!pipeline)
		return (NULL);
	pipeline->argv = malloc(sizeof(char *) * (cmd_len - redir_count * 2 + 1));
	if (!pipeline->argv)
	{
		free(pipeline);
		return (NULL);
	}
	i = 0;
	head.next = NULL;
	redir = &head;
	while (1)
	{
		if ((*token)->kind == TK_WORD)
		{
			pipeline->argv[i++] = ft_strdup((*token)->value);
			*token = (*token)->next;
		}
		else if ((*token)->kind == TK_REDIR)
		{
			redir = redir_add(redir, *token);
			if (!redir)
			{
				free_command(pipeline, redir);
				return (NULL);
			}
			*token = ((*token)->next)->next;
		}
		else
			break ;
	}
	pipeline->argv[i] = NULL;
	pipeline->redir = head.next;
	return (pipeline);
}

int	get_cmd_len(t_token *token)
{
	int	len;

	len = 0;
	while (token->kind == TK_WORD || token->kind == TK_REDIR)
	{
		len++;
		token = token->next;
	}
	return (len);
}

int	get_redir_count(t_token *token)
{
	int	count;

	count = 0;
	while (token->kind == TK_WORD || token->kind == TK_REDIR)
	{
		if (token->kind == TK_REDIR)
		{
			count++;
			token = (token->next)->next;
		}
		else
			token = token->next;
	}
	return (count);
}

t_pipeline	*consume_command(t_token **token)
{
	int			cmd_len;
	int			redir_count;

	if ((*token)->kind != TK_WORD && (*token)->kind != TK_REDIR)
		return (NULL);
	cmd_len = get_cmd_len(*token);
	redir_count = get_redir_count(*token);
	return (get_command(token, cmd_len, redir_count));
}

t_pipeline	*consume_pipeline(t_token **token)
{
	t_pipeline	head;
	t_pipeline	*pipeline;

	head.next = NULL;
	pipeline = &head;
	while ((*token)->kind == TK_WORD || (*token)->kind == TK_REDIR)
	{
		pipeline = pipeline->next;
		pipeline = consume_command(token);
		if ((*token)->kind == TK_PIPE)
			*token = (*token)->next;
	}
	return (head.next);
}

int consume(t_token_kind kind, t_token **token)
{
	if ((*token)->kind != kind)
		return (0);
	*token = (*token)->next;
	return (1);
}
