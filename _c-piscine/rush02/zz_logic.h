/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zz_logic.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:35:51 by apuddu            #+#    #+#             */
/*   Updated: 2023/11/12 20:35:53 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ZZ_LOGIC_H
# define ZZ_LOGIC_H
# include "parser.h"
# include "print_num.h"
# include "string.h"
# include <stdlib.h>
# include <unistd.h>

void	convert_to_ascii2(char *nbr_ascii, char *dict, int length, int n_group);
int		controll_float(char *nbr_ascii);
char	*clean_str(char *nbr_ascii);
int		ft_strlen(char *str);
void	convert_to_ascii(char *nbr_ascii, char *dict);

// pads the string with '0's to the left until its length is a multiple of 3
char	*make_reg(char *a, int n_groups)
{
	int		len;
	int		diff;
	char	*res;
	int		i;

	len = ft_strlen(a);
	diff = n_groups * 3 - len;
	res = (char *)malloc(n_groups * 3 + 1);
	i = 0;
	while (i < diff)
	{
		res[i] = '0';
		i++;
	}
	i = 0;
	while (i < len)
	{
		res[i + diff] = a[i];
		i++;
	}
	res[i + diff] = 0;
	return (res);
}

void	convert_to_ascii(char *nbr_ascii, char *dict)
{
	int		length;
	int		n_group;
	char	**keys;
	char	**values;

	if (controll_float(nbr_ascii) || *nbr_ascii == '-')
	{
		write(1, "Error\n", 6);
		return ;
	}
	keys = get_keys();
	values = parse_values(dict);
	nbr_ascii = clean_str(nbr_ascii);
	length = ft_strlen(nbr_ascii);
	n_group = length / 3;
	n_group += (length % 3 != 0);
	if (29 + n_group > 42)
	{
		ft_putstr("Error\n");
		return ;
	}
	nbr_ascii = make_reg(nbr_ascii, n_group);
	parse(nbr_ascii, keys, values, n_group);
}

int	controll_float(char *nbr_ascii)
{
	int	i;

	i = 0;
	while (nbr_ascii[i] != '\0')
	{
		if (nbr_ascii[i] == '.')
			return (1);
		i++;
	}
	return (0);
}
#endif
