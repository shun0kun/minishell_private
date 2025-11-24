#include "../minishell.h"
#include "private.h"

void	free_cmd(t_cmd *cmd, t_redir *redir)
{
	size_t	i;
	t_redir	*cur;
	t_redir	*next;

	if (!cmd)
		return ;
	i = 0;
	if (cmd->argv)
	{
		while (cmd->argv[i])
		{
			free(cmd->argv[i]);
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
	free(cmd);
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

t_cmd	*create_cmd(int cmd_len, int redir_count, t_token *token)
{
	t_cmd	*cmd;
	t_redir	head;
	t_redir	*redir;
	size_t	i;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *) * (cmd_len - redir_count * 2 + 1));
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	i = 0;
	head.next = NULL;
	redir = &head;
	while (1)
	{
		if (token->kind == TK_WORD)
		{
	

			cmd->argv[i] = ft_strdup(token->value);

			i++;
			token = token->next;
		}
		else if (token->kind == TK_REDIR)
		{

			redir = redir_add(redir, token);

			if (!redir)
			{
				free_cmd(cmd, head.next);
				return (NULL);
			}
			token = (token->next)->next;
		}
		else
			break ;
	}
	cmd->argv[i] = NULL;
	cmd->redir = head.next;
	return (cmd);
}

t_cmd	*consume_cmd(t_token **token)
{
	t_cmd	*cmd;
	t_token	*token_cp;
	int		cmd_len;
	int		redir_count;

	if ((*token)->kind != TK_WORD && (*token)->kind != TK_REDIR)
		return (NULL);
	token_cp = *token;
	cmd_len = 0;
	redir_count = 0;
	while (1)
	{
		if ((*token)->kind == TK_WORD)
		{
			cmd_len++;
			*token = (*token)->next;
		}
		else if ((*token)->kind == TK_REDIR)
		{
			redir_count++;
			cmd_len += 2;
			*token = ((*token)->next)->next;
		}
		else
			break ;
	}

	cmd = create_cmd(cmd_len, redir_count, token_cp);

	if (!cmd)
		return (NULL);
	return (cmd);
}

int consume(t_token_kind kind, t_token **token)
{
	if ((*token)->kind != kind)
		return (0);
	*token = (*token)->next;
	return (1);
}
