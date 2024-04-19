/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcoletta <pcoletta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:42:13 by pcoletta          #+#    #+#             */
/*   Updated: 2022/01/10 16:03:06 by pcoletta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*curr;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	start = ft_lstnew(f(lst->content));
	curr = start;
	if (start == NULL)
		return (NULL);
	while (lst && lst->next)
	{
		curr->next = ft_lstnew(f(lst->content));
		if (curr->next == NULL)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		curr = curr->next;
		lst = lst->next;
	}
	return (start);
}
