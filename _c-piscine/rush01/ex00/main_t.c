/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 23:01:25 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/05 23:02:13 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char	*inserimenti1(char n, char n2, int tentativo);
char	*inserimenti2(char n, char n2, int tentativo);
char	*inserimenti3(char n, char n2, int tentativo);
void	tabella4x42(char *stringa, char matrice[4][4]);
char	*combo_riga(char *stringa, int i, int x, char matrice[4][4]);
int		controllo_colonne(char *ho, char matrice[4][4]);

void	tabella4x4(char *stringa, char matrice[4][4])
{
	char	*hola;

	hola = inserimenti1(stringa[0], stringa[4], 1);
	if (*hola == 'f')
		hola = inserimenti2(stringa[0], stringa[4], 1);
	if (*hola == 'f')
		hola = inserimenti3(stringa[0], stringa[4], 1);
	matrice[0][0] = hola[0];
	matrice[1][0] = hola[1];
	matrice[2][0] = hola[2];
	matrice[3][0] = hola[3];
	hola = inserimenti1(stringa[3], stringa[7], 1);
	if (*hola == 'f')
		hola = inserimenti2(stringa[3], stringa[7], 1);
	if (*hola == 'f')
		hola = inserimenti3(stringa[3], stringa[7], 1);
	matrice[0][3] = hola[0];
	matrice[1][3] = hola[1];
	matrice[2][3] = hola[2];
	matrice[3][3] = hola[3];
	tabella4x42(stringa, matrice);
}

void	tabella4x42(char *stringa, char matrice[4][4])
{
	int		i;
	int		x;
	char	*hola;

	i = 8;
	x = 0;
	while (x != 4)
	{
		hola = combo_riga(stringa, i, x, matrice);
		if (*hola == 'f')
			matrice[0][0] = '0';
		else
		{
			matrice[x][0] = hola[0];
			matrice[x][1] = hola[1];
			matrice[x][2] = hola[2];
			matrice[x][3] = hola[3];
		}
		x++;
		i++;
	}
}

char	*combo_riga(char *stringa, int i, int x, char matrice[4][4])
{
	char	*ho;
	int		f;

	f = 1;
	while (f < 7)
	{
		ho = inserimenti1(stringa[i], stringa[i + 4], f);
		if (*ho == 'f')
			ho = inserimenti2(stringa[i], stringa[i + 4], f);
		if (*ho == 'f')
			ho = inserimenti3(stringa[i], stringa[i + 4], f);
		if (*ho == 'f')
			f++;
		else if ((ho[0] == matrice[x][0] || ho[3] == matrice[x][3])
			&& controllo_colonne(ho, matrice))
			f = 7;
		else
			f++;
	}
	return (ho);
}

int	controllo_colonne(char *ho, char matrice[4][4])
{
	int		i;

	i = 0;
	while (i != 4)
	{
		if (matrice[i][1] == ho[1] || matrice[i + 1][2] == ho[2])
			return (0);
		else
			return (1);
		i++;
	}
	return (0);
}
