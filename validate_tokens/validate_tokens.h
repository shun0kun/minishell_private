#ifndef CHECK_TOKENS_H
# define CHECK_TOKENS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../common_def.h"

// typedef enum e_token_type
// {
// 	TOK_NO,
// 	TOK_WORD,
// 	TOK_RED,
// 	TOK_PIPE,
// 	TOK_ANDOR,
// 	TOK_KAKKOO,
// 	TOK_KAKKOC,
// 	TOK_EOF
// } t_token_type;

// typedef struct s_token
// {
// 	t_token_type	type;
// 	char			*value;
// 	struct s_token	*next;
// }	t_token;

typedef enum e_state_val
{
	START,
	AFTER_WORD,
	AFTER_RED,
	AFTER_PIPE,
	AFTER_ANDOR,
	AFTER_PARENS,
	ERROR
}	t_state_val;

int	validate_tokens(t_token *token);

#endif