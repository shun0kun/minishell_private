/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shimotsukasashunsuke <shimotsukasashuns    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 12:19:02 by sshimots          #+#    #+#             */
/*   Updated: 2025/12/05 09:15:00 by shimotsukas      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*q;

	if (!lst || !del)
		return ;
	p = *lst;
	while (p)
	{
		del(p->content);
		q = p->next;
		free(p);
		p = q;
	}
	*lst = NULL;
}
