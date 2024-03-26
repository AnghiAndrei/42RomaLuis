/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_a.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 21:48:28 by apuddu            #+#    #+#             */
/*   Updated: 2023/11/12 21:48:30 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*clean_str(char *nbr_ascii)
{
	char	*str;

	while (*nbr_ascii == '0' || *nbr_ascii == ' ' || (*nbr_ascii >= 9
			&& *nbr_ascii <= 13))
		nbr_ascii++;
	str = nbr_ascii;
	while (*str >= '0' && *str <= '9')
		str++;
	*str = '\0';
	return (nbr_ascii);
}

int	ft_strlen(char *str)
{
	unsigned int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

char	*split(char *str, char sep)
{
	while (*str)
	{
		if (*str == sep)
		{
			*str = 0;
			return (str + 1);
		}
		str++;
	}
	return (0);
}
