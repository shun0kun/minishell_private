#ifndef PRIVATE_H
# define PRIVATE_H

# include "../minishell.h"

void		free_cmd(t_pipeline *pipeline, t_redir *redir);
t_redir		*redir_add(t_redir *redir, t_token *token);
t_pipeline	*get_command(t_token **token, int cmd_len, int redir_count);
t_pipeline	*consume_command(t_token **token);
t_pipeline	*consume_pipeline(t_token **token);
int 		consume(t_token_kind kind, t_token **token);

#endif