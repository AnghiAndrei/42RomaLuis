/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <aanghi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 15:23:59 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/17 15:05:41 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num_elements, size_t size_of_element)
{
	unsigned char		*array;
	size_t				i;

	if (num_elements && size_of_element
		&& num_elements > 4294967295 / size_of_element)
		return (NULL);
	array = (unsigned char *)malloc(num_elements * size_of_element);
	if (!array)
		return (NULL);
	i = 0;
	while (i != num_elements * size_of_element)
	{
		array[i] = 0;
		i++;
	}
	return (array);
}
