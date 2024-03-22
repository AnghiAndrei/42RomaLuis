/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 08:17:36 by aanghi            #+#    #+#             */
/*   Updated: 2024/01/10 08:17:36 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lstadd_back(t_philo **lst, t_philo *new)
{
	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else if (!(lst == NULL || new == NULL))
	{
		while ((*lst)->nextphilo != NULL)
			lst = &(*lst)->nextphilo;
		(*lst)->nextphilo = new;
	}
}
