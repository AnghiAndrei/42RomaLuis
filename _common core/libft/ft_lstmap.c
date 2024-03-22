/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:17:36 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/10 08:17:36 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p1;
	t_list	*new_lst;

	new_lst = NULL;
	while (lst != NULL)
	{
		p1 = ft_lstnew(f(lst->content));
		if (p1 == NULL)
		{
			ft_lstclear(&p1, del);
			return (NULL);
		}
		ft_lstadd_back(&new_lst, p1);
		lst = lst->next;
	}
	return (new_lst);
}
