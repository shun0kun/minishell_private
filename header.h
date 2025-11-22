#ifndef HEADER_H
# define HEADER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

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

typedef enum e_state
{
	OUT_QUOTE,
	IN_SINGLE,
	IN_DOUBLE
}	t_state;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_buf
{
	char	*data;
	size_t	len;
	size_t	cap;
}	t_buf;

t_token 		*tokenize(char *str);
int				is_number(char c);
int				is_alphabet(char c);
int				is_space(char c);
int				is_operator(char *str);
t_token			*new_token(t_token *token);
t_token_type	get_operation_token_type(char *str);
int				get_operation_value(t_token *token, char *str);
int				get_word_value(t_token *token, char *str);

void			*ft_memmove(void *dest, const void *src, size_t n);
char			*ft_strndup(const char *s, size_t n);

t_buf			*buf_create(void);
int				buf_add(t_buf *buf, char c);
int				buf_extend(t_buf *buf);
void			buf_destroy(t_buf *buf);
int				buf_init(t_buf *buf);

int	get_env(char **env, char *str);

#endif
