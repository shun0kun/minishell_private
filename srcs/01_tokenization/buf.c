#include "../minishell.h"
#include "private.h"

int	buf_add(t_buf *buf, char c)
{
	if (!buf)
		return (-1);
	if (buf->len >= buf->cap)
	{
		if (buf_extend(buf) < 0)
			return (-1);
	}
	buf->data[buf->len] = c;
	buf->len += 1;
	return (0);
}

int	buf_extend(t_buf *buf)
{
	char	*extended_data;
	size_t	new_cap;

	if (!buf)
		return (-1);
	new_cap = buf->cap * 2;
	extended_data = malloc(new_cap);
	if (!extended_data)
		return (-1);
	ft_memmove(extended_data, buf->data, buf->len);
	free(buf->data);
	buf->data = extended_data;
	buf->cap = new_cap;
	return (0);
}

int	buf_init(t_buf *buf)
{
	size_t	cap;

	cap = 64;
	buf->data = malloc(cap);
	if (!buf->data)
		return (-1);
	buf->len = 0;
	buf->cap = cap;
	return (0);
}
