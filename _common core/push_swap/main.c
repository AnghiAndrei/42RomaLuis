/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:17:21 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/28 17:39:37 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;
	t_stack		*cur;
	t_stack		*next;

	stack_a = NULL;
	stack_b = NULL;
	if (argc >= 2)
	{
		ceck_input(argc, argv);
		fill_stack(&stack_a, argc, argv, 0);
		if (ft_lstlen(stack_a) == 0)
			error_message();
		sort(&stack_a, &stack_b);
		cur = stack_a;
		while (cur != NULL)
		{
			next = cur->next;
			free(cur);
			cur = next;
		}
	}
	return (0);
}
