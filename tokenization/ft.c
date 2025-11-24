#include "../minishell.h"
#include "private.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t	i;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s && d < s + n)
	{
		i = n;
		while (i--)
		{
			d[i] = s[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return(dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((const unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*res;

	len = ft_min(ft_strlen(s), n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_memcpy(res, s, len);
	res[len] = '\0';
	return (res);
}

// char	*ft_strjoin()
// {

// }

//ft_strnlenにすると効率化される！