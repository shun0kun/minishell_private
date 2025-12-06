#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "env/env.h"
# include "ft/ft.h"

typedef enum e_token_kind
{
	TK_WORD,
	TK_REDIR,
	TK_PIPE,
	TK_LPAREN,
	TK_RPAREN,
	TK_AND,
	TK_OR,
	TK_EOF
} t_token_kind;

typedef struct s_token
{
	t_token_kind	kind;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef enum e_node_kind
{
	ND_PIPELINE,
	ND_AND,
	ND_OR
}	t_node_kind;

typedef enum e_redir_kind
{
	IN,
	OUT,
	APPEND,
	HEREDOC
}	t_redir_kind;

typedef struct s_redir
{
	t_redir_kind	kind;
	char			*filename;
	int				heredoc_fd;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipeline
{
	char				**argv;
	t_redir				*redir;
	struct s_pipeline	*next;
}	t_pipeline;

typedef struct s_node
{
	t_node_kind		kind;
	t_pipeline		*pipeline;
	struct s_node	*lhs;
	struct s_node	*rhs;
}	t_node;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;

}	t_shell;

t_token *tokenize(char *str, t_shell *shell);

int		validate_tokens(t_token *token);

t_node	*list(t_token **token);

void	execute_ast(t_node *node, t_shell *shell);

#endif
