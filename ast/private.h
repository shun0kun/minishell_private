#ifndef PRIVATE_H
# define PRIVATE_H

# include "../minishell.h"

void	free_cmd(t_cmd *cmd, t_redir *redir);
t_redir	*add_redir(t_redir *redir, t_token *token);
t_cmd	*create_cmd(int cmd_len, int redir_count, t_token *token);
t_cmd	*consume_cmd(t_token **token);
int 	consume(t_token_kind kind, t_token **token);

int		ft_strlen(const char *s);
char	*ft_strdup(const char *s);

#endif