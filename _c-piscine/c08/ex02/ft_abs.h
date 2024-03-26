/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 09:54:10 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/16 09:55:31 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ABS_H
# define FT_ABS_H

# define ABS(Value) ft_abs(Value)

int	ft_abs(int Value)
{
	if (Value < 0)
		return (-Value);
	return (Value);
}

#endif
