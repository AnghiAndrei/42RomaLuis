/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 22:57:40 by apuddu            #+#    #+#             */
/*   Updated: 2023/11/12 22:57:42 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "string.h"

int		g_whitespace = 0;

void	put_check_whitespace(char *s)
{
	if (g_whitespace)
		ft_putstr(" ");
	ft_putstr(s);
	g_whitespace = 1;
}

int	do_hundreds(char *g, char **values)
{
	g[3] = 0;
	if (g[0] != '0')
	{
		if (!values[g[0] - '0'])
			return (1);
		put_check_whitespace(values[g[0] - '0']);
		put_check_whitespace(values[28]);
	}
	return (0);
}

int	do_tens(char *g, char **keys, char **values)
{
	int	x;

	if (g[1] != '0')
	{
		x = index_of(keys, 42, g + 1);
		if (x != -1)
		{
			put_check_whitespace(values[x]);
			return (0);
		}
		g[2] = '0';
		x = index_of(keys, 42, g + 1);
		if (x != -1)
			put_check_whitespace(values[x]);
		else
			return (-1);
	}
	return (0);
}

int	print_group(char *g, char **keys, char **values)
{
	char	temp;
	int		t2;

	t2 = g[2] - '0';
	temp = g[3];
	if (do_hundreds(g, values))
		return (-1);
	if (do_tens(g, keys, values))
		return (-1);
	if (g[1] > '1' && t2)
	{
		if (!values[t2])
			return (-1);
		put_check_whitespace(values[t2]);
	}
	g[3] = temp;
	return (0);
}

void	parse(char *nbr_ascii, char **keys, char **values, int n_group)
{
	int	i;
	int	write_n;

	if(ft_strlen(nbr_ascii) == 0)
	{
		if(values[0] == NULL)
		{
			ft_putstr("Dict Error\n");
			return ;
		}
		ft_putstr(values[0]);
	}
	write_n = 0;
	i = 0;
	while (i < n_group)
	{
		write_n = print_group(nbr_ascii, keys, values);
		if (write_n == -1)
		{
			ft_putstr("Dict Error\n");
			return ;
		}
		if (nbr_ascii[0] != '0' || nbr_ascii[1] != '0' || nbr_ascii[2] != '0')
			put_check_whitespace(values[29 + n_group - i - 1]);
		i++;
		nbr_ascii += 3;
	}
	ft_putstr("\n");
}
