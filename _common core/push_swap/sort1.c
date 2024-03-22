/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 10:58:54 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/26 14:49:08 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_3_b(t_stack **a, t_stack **b, int len)
{
	if (len == 1)
		push(a, b, 'a');
	else if (len == 2)
	{
		if ((*b)->data < (*b)->next->data)
			swap(b, "b", 0);
		while (len--)
			push(a, b, 'a');
	}
	else if (len == 3)
	{
		while (len || !((*a)->data < (*a)->next->data
				&& (*a)->next->data < (*a)->next->next->data))
		{
			if (len == 1 && (*a)->data > (*a)->next->data)
				swap(a, "a", 0);
			else if ((len == 1
					|| (len >= 2 && (*b)->data > (*b)->next->data)
					|| (len == 3
						&& (*b)->data > (*b)->next->next->data)) && len--)
				push(a, b, 'a');
			else
				swap(b, "b", 0);
		}
	}
}

void	quick_sort_3_a_b(t_stack **a, t_stack **b, int len)
{
	if (len == 3 && ft_lstlen((*a)) == 3)
		sort3(a, (*a), (*a)->next, (*a)->next->next);
	else if (len == 2)
	{
		if ((*a)->data > (*a)->next->data)
			swap(a, "a", 0);
	}
	else if (len == 3)
	{
		while (len != 3 || !((*a)->data < (*a)->next->data
				&& (*a)->next->data < (*a)->next->next->data))
		{
			if (len == 3 && (*a)->data > (*a)->next->data
				&& (*a)->next->next->data)
				swap(a, "a", 0);
			else if (len == 3
				&& !((*a)->next->next->data > (*a)->data
					&& (*a)->next->next->data > (*a)->next->data) && len--)
				push(a, b, 'b');
			else if ((*a)->data > (*a)->next->data)
				swap(a, "a", 0);
			else if (len++)
				push(a, b, 'a');
		}
	}
}
