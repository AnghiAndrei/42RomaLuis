/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:59:23 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/26 16:09:23 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort(t_stack **a, t_stack **stack_b)
{
	if (!check_sorted_asc((*a), ft_lstlen((*a))))
	{
		if (ft_lstlen((*a)) == 2
			&& (*a)->data > (*a)->next->data)
			swap(a, "a", 0);
		else if (ft_lstlen((*a)) == 3)
			sort3(a, (*a), (*a)->next, (*a)->next->next);
		else
			quick_sort_a(a, stack_b, 0, ft_lstlen((*a)));
	}
}

void	sort3(t_stack **stack, t_stack *p, t_stack *s, t_stack *t)
{
	if (p->data < s->data && p->data < t->data && s->data > t->data)
	{
		swap(stack, "a", 0);
		rotate(stack, "a", 0);
	}
	else if (p->data > s->data && p->data > t->data && s->data > t->data)
	{
		swap(stack, "a", 0);
		rrotate(stack, "a", 0);
	}
	else if (p->data < s->data && p->data > t->data && s->data > t->data)
		rrotate(stack, "a", 0);
	else if (p->data > s->data && p->data > t->data && s->data < t->data)
		rotate(stack, "a", 0);
	else if (p->data > s->data && p->data < t->data && s->data < t->data)
		swap(stack, "a", 0);
}

int	quick_sort_a(t_stack **stack_a, t_stack **stack_b, int n_r, int len)
{
	int		len_ori;
	int		pivot;

	if (check_sorted_asc((*stack_a), len) == 1)
		return (1);
	len_ori = len;
	if (len <= 3)
	{
		quick_sort_3_a_b(stack_a, stack_b, len);
		return (1);
	}
	if (!get_pivot((*stack_a), len, &pivot))
		return (0);
	while (len != len_ori / 2 + len_ori % 2)
	{
		if ((*stack_a)->data < pivot && (len--))
			push(stack_a, stack_b, 'b');
		else if (++n_r)
			rotate(stack_a, "a", 0);
	}
	while (n_r--)
		rrotate(stack_a, "a", 0);
	return (quick_sort_a(stack_a, stack_b, 0, len_ori / 2 + len_ori % 2)
		&& quick_sort_b(stack_a, stack_b, 0, len_ori / 2));
}

int	quick_sort_b(t_stack **stack_a, t_stack **stack_b, int n_r, int len)
{
	int		pivot;
	int		len_ori;

	if (check_sorted_des((*stack_b), len) == 1)
		while (len--)
			push(stack_a, stack_b, 'a');
	if (len <= 3)
	{
		sort_3_b(stack_a, stack_b, len);
		return (1);
	}
	len_ori = len;
	if (!get_pivot((*stack_b), len, &pivot))
		return (0);
	while (len != len_ori / 2)
	{
		if ((*stack_b)->data >= pivot && len--)
			push(stack_a, stack_b, 'a');
		else if (++n_r)
			rotate(stack_b, "b", 0);
	}
	while (len_ori / 2 != ft_lstlen((*stack_b)) && n_r--)
		rrotate(stack_b, "b", 0);
	return (quick_sort_a(stack_a, stack_b, 0, len_ori / 2 + len_ori % 2)
		&& quick_sort_b(stack_a, stack_b, 0, len_ori / 2));
}
