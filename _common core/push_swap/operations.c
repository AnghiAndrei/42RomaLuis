/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 06:30:15 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/14 06:56:00 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(t_stack **stack, char *c, int s)
{
	t_stack	*next_b;
	int		tmp;

	next_b = (*stack)->next;
	tmp = (*stack)->data;
	(*stack)->data = next_b->data;
	next_b->data = tmp;
	if (s == 0)
	{
		ft_putstr("s");
		ft_putstr(c);
		ft_putstr("\n");
	}
}

void	push(t_stack **stack_a, t_stack **stack_b, char c)
{
	t_stack	*tmp;

	if (c == 'b')
	{
		if (*stack_a != NULL)
		{
			tmp = *stack_a;
			*stack_a = (*stack_a)->next;
			tmp->next = *stack_b;
			*stack_b = tmp;
		}
	}
	else
	{
		if (*stack_b != NULL)
		{
			tmp = *stack_b;
			*stack_b = (*stack_b)->next;
			tmp->next = *stack_a;
			*stack_a = tmp;
		}
	}
	ft_putstr("p");
	write(1, &c, 1);
	ft_putstr("\n");
}

void	rotate(t_stack **stack, char *c, int s)
{
	t_stack	*first;
	t_stack	*last;

	first = *stack;
	*stack = (*stack)->next;
	last = *stack;
	while (last->next != NULL)
		last = last->next;
	last->next = first;
	first->next = NULL;
	if (s == 0)
	{
		ft_putstr("r");
		ft_putstr(c);
		ft_putstr("\n");
	}
}

void	rrotate(t_stack **stack, char *c, int s)
{
	t_stack	*penultimate;
	t_stack	*last;

	penultimate = *stack;
	while (penultimate->next->next != NULL)
		penultimate = penultimate->next;
	last = penultimate->next;
	penultimate->next = NULL;
	last->next = *stack;
	*stack = last;
	if (s == 0)
	{
		ft_putstr("rr");
		ft_putstr(c);
		ft_putstr("\n");
	}
}

void	combo(t_stack **stack_a, t_stack **stack_b, int r)
{
	if (r == 0)
	{
		swap(stack_a, "a", 1);
		swap(stack_b, "b", 1);
		ft_putstr("ss");
		ft_putstr("\n");
	}
	if (r == 2)
	{
		rotate(stack_a, "a", 1);
		rotate(stack_b, "b", 1);
		ft_putstr("rr");
		ft_putstr("\n");
	}
	if (r == 3)
	{
		rrotate(stack_a, "a", 1);
		rrotate(stack_b, "b", 1);
		ft_putstr("rrr");
		ft_putstr("\n");
	}
}
