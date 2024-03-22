/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilitis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 21:20:17 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/13 21:20:17 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	fill_stack(t_stack **stack, int argc, char **argv, int i)
{
	char	**split;

	if (argc == 2)
	{
		split = ft_split(argv[1], ' ');
		while (split[i] != NULL)
		{
			if (ft_strlen(split[i]) <= 11)
				controll1(stack, ft_atoi(split[i]));
			else
				error_message();
			free(split[i++]);
		}
		free(split);
	}
	else
	{
		while (argv[++i])
		{
			if (ft_strlen(argv[i]) <= 11)
				controll1(stack, ft_atoi(argv[i]));
			else
				error_message();
		}
	}
}

int	get_pivot(t_stack *stack, int len, int *pivot)
{
	int	*tmp;
	int	i;

	tmp = (int *)malloc(sizeof(int) * len);
	if (!tmp)
		return (0);
	i = 0;
	while (i < len)
	{
		tmp[i++] = stack->data;
		stack = stack->next;
	}
	bubble_sort(tmp, len);
	*pivot = tmp[len / 2];
	free(tmp);
	return (1);
}

void	bubble_sort(int *stack_c, int len)
{
	int		tmp;
	int		i;

	i = 0;
	while (i != len - 1)
	{
		if (stack_c[i] > stack_c[i + 1])
		{
			tmp = stack_c[i];
			stack_c[i] = stack_c[i + 1];
			stack_c[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

int	check_sorted_asc(t_stack *stack, int len)
{
	int		i;

	i = 0;
	while (stack->next != NULL && i != len)
	{
		if (stack->data > stack->next->data)
			return (0);
		stack = stack->next;
	}
	return (1);
}

int	check_sorted_des(t_stack *stack, int len)
{
	int		i;

	i = 0;
	while (stack->next != NULL && i != len)
	{
		if (stack->data < stack->next->data)
			return (0);
		stack = stack->next;
	}
	return (1);
}
