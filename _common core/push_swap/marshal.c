/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   marshal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 02:00:04 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/01 01:03:31 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error_message(void)
{
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}

void	ceck_input(int argc, char **argv)
{
	int		i;

	i = 0;
	if (argc == 2)
	{
		while (argv[1][i] != '\0')
		{
			while (argv[1][i] == ' ' || (argv[1][i] >= 9 && argv[1][i] <= 13))
				i++;
			if (argv[1][i] == '\0')
				break ;
			if ((argv[1][i] == '+' || argv[1][i] == '-')
					&& (argv[1][i + 1] >= '0' && argv[1][i + 1] <= '9'))
				i++;
			if (argv[1][i] >= '0' && argv[1][i] <= '9')
				i++;
			else
				error_message();
		}
		if (i == 0)
			error_message();
	}
}

void	controll1(t_stack **stack, int number)
{
	t_stack		*cur;
	t_stack		*next_block;

	if (*stack != NULL)
	{
		cur = *stack;
		while (cur->next != NULL)
		{
			if (cur->data == number)
				error_message();
			cur = cur->next;
		}
		if (cur->data == number)
			error_message();
	}
	next_block = (t_stack *)malloc(sizeof(t_stack));
	if (next_block == NULL)
		error_message();
	next_block->data = number;
	next_block->next = NULL;
	ft_lstadd_back(stack, next_block);
}
