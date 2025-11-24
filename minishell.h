#ifndef COMMON_DEF_H
# define COMMON_DEF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
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
	ND_CMD,
	ND_PIPE,
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
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redir;
}	t_cmd;

typedef struct s_node
{
	t_node_kind		kind;
	t_cmd			*cmd;
	struct s_node	*lhs;
	struct s_node	*rhs;
}	t_node;

t_token *tokenize(char *str);

int	validate_tokens(t_token *token);

t_node	*list(t_token **token);

void print_ast(t_node *node);



#endif
