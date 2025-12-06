#ifndef PRIVATE_H
# define PRIVATE_H

# include "../minishell.h"

typedef enum e_state
{
	OUT_QUOTE,
	IN_SINGLE,
	IN_DOUBLE
}	t_state;

typedef struct s_buf
{
	char	*data;
	int		len;
	int		cap;
}	t_buf;

int				is_number(char c);
int				is_alphabet(char c);
int				is_space(char c);
int				is_operator(char *str);
t_token			*new_token(t_token *token);
t_token			*get_last_token(t_token *token);
t_token_kind	get_operation_token_type(char *str);
int				get_operation_value(t_token *token, char *str);
int				get_word_value(t_token *token, char *str);
size_t			ft_strlen(const char *s);
void			*ft_memmove(void *dest, const void *src, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
int				ft_min(int a, int b);
char			*ft_strndup(const char *s, size_t n);
int				get_env(char **env_val, char *str);
int				buf_add(t_buf *buf, char c);
int				buf_extend(t_buf *buf);
int				buf_init(t_buf *buf);

#endif