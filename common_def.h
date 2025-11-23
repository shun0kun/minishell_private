#ifndef COMMON_DEF_H
# define COMMON_DEF_H

typedef enum e_token_type
{
	TOK_NO,
	TOK_WORD,
	TOK_RED,
	TOK_PIPE,
	TOK_ANDOR,
	TOK_KAKKOO,
	TOK_KAKKOC,
	TOK_EOF
} t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

#endif