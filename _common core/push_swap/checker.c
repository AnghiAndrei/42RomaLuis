/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 10:59:50 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/27 11:51:46 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push2(t_stack **stack_a, t_stack **stack_b, char c)
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
}

static void	ceck_moves2(t_stack **stack_a, t_stack **stack_b, char *line)
{
	if (!ft_strncmp(line, "sa", 2))
		swap(stack_a, "a", 1);
	else if (!ft_strncmp(line, "sb", 2))
		swap(stack_b, "b", 1);
	else if (!ft_strncmp(line, "ss", 2))
	{
		swap(stack_a, "a", 1);
		swap(stack_b, "b", 1);
	}
	if (!ft_strncmp(line, "pa", 2))
		push2(stack_a, stack_b, 'a');
	else if (!ft_strncmp(line, "pb", 2))
		push2(stack_a, stack_b, 'b');
}

static void	ceck_moves(t_stack **stack_a, t_stack **stack_b, char *line)
{
	if (!ft_strncmp(line, "rra", 3))
		rrotate(stack_a, "a", 1);
	else if (!ft_strncmp(line, "rrb", 3))
		rrotate(stack_b, "b", 1);
	else if (!ft_strncmp(line, "ra", 2))
		rotate(stack_a, "a", 1);
	else if (!ft_strncmp(line, "rb", 2))
		rotate(stack_b, "b", 1);
	else if (!ft_strncmp(line, "rrr", 3))
	{
		rrotate(stack_a, "a", 1);
		rrotate(stack_b, "b", 1);
	}
	ceck_moves2(stack_a, stack_b, line);
}

static int	ceck(char *line)
{
	if (line == NULL)
		return (0);
	else if (!ft_strncmp(line, "sa", 2))
		return (0);
	else if (!ft_strncmp(line, "sb", 2))
		return (0);
	else if (!ft_strncmp(line, "pa", 2))
		return (0);
	else if (!ft_strncmp(line, "pb", 2))
		return (0);
	else if (!ft_strncmp(line, "ra", 2))
		return (0);
	else if (!ft_strncmp(line, "rb", 2))
		return (0);
	else if (!ft_strncmp(line, "rra", 3))
		return (0);
	else if (!ft_strncmp(line, "rrb", 3))
		return (0);
	else if (!ft_strncmp(line, "rr", 2))
		return (0);
	else if (!ft_strncmp(line, "rrr", 3))
		return (0);
	else if (!ft_strncmp(line, "ss", 3))
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	char		*l;

	stack_a = NULL;
	stack_b = NULL;
	if (argc >= 2)
	{
		ceck_input(argc, argv);
		fill_stack(&stack_a, argc, argv, 0);
		l = get_next_line(0);
		while (l != NULL && ceck(l) == 0)
		{
			ceck_moves(&stack_a, &stack_b, l);
			free(l);
			l = get_next_line(0);
		}
		if (check_sorted_asc(stack_a, ft_lstlen(stack_a)) == 1
			&& ft_lstlen(stack_b) == 0 && ceck(l) == 0)
			write(1, "OK\n", 3);
		else
			write(1, "KO\n", 3);
		free(l);
	}
	return (0);
}
