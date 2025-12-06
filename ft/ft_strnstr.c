/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimotsukasashunsuke <shimotsukasashuns    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 19:09:27 by sshimots          #+#    #+#             */
/*   Updated: 2025/12/05 09:15:00 by shimotsukas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

int	ft_check(const char *str, const char *little, size_t rest)
{
	size_t	i;

	i = 0;
	while (i < rest && str[i] && little[i])
	{
		if (str[i] != little[i])
			return (0);
		i++;
	}
	if (!little[i])
		return (1);
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (i < len && big[i])
	{
		if (big[i] == little[0] && ft_check(&big[i], little, len - i))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
