/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:00:26 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/05 23:00:37 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int		elimina_combo(char *argv);
void	tabella4x4(char *stringa, char matrice[4][4]);

void	rimuovi_spazi(char *stringa)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (stringa[i] != '\0')
	{
		if (stringa[i] != ' ')
		{
			stringa[j] = stringa[i];
			j++;
		}
		i++;
	}
	stringa[j] = '\0';
}

void	stampa(char matrice[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i != 4)
	{
		j = 0;
		while (j != 4)
		{
			write(1, &matrice[i][j], 1);
			if (j < 3)
				write(1, " ", 1);
			j++;
		}
		i++;
		write(1, "\n", 1);
	}
}

int	main(int argc, char *argv[])
{
	char		*stringa;
	char		matrice[4][4];

	if (argc != 2)
	{
		write(1, "Error\n", 6);
		return (0);
	}
	stringa = argv[1];
	rimuovi_spazi(stringa);
	if (elimina_combo(stringa))
	{
		write(1, "Error\n", 6);
		return (0);
	}
	tabella4x4(stringa, matrice);
	if (matrice[0][0] != '0')
		stampa(matrice);
	else
		write(1, "Error\n", 6);
	return (0);
}
