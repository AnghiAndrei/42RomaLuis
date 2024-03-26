/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 22:56:20 by aanghi            #+#    #+#             */
/*   Updated: 2023/11/05 22:58:58 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*inserimenti1(char n, char n2, int tentativo)
{
	if (n == '4' && n2 == '1')
		return ("1234");
	if (n == '1' && n2 == '4')
		return ("4321");
	if (n == '3' && n2 == '2' && tentativo == 1)
		return ("1342");
	if (n == '3' && n2 == '2' && tentativo == 2)
		return ("1243");
	if (n == '3' && n2 == '2' && tentativo == 3)
		return ("2341");
	if (n == '3' && n2 == '1' && tentativo == 1)
		return ("2134");
	if (n == '3' && n2 == '1' && tentativo == 2)
		return ("2314");
	if (n == '3' && n2 == '1' && tentativo == 3)
		return ("1324");
	if (n == '2' && n2 == '3' && tentativo == 1)
		return ("2431");
	if (n == '2' && n2 == '3' && tentativo == 2)
		return ("3421");
	return ("f");
}

char	*inserimenti2(char n, char n2, int tentativo)
{
	if (n == '2' && n2 == '3' && tentativo == 3)
		return ("1432");
	if (n == '2' && n2 == '1' && tentativo == 1)
		return ("3214");
	if (n == '2' && n2 == '1' && tentativo == 2)
		return ("3124");
	if (n == '1' && n2 == '3' && tentativo == 1)
		return ("4312");
	if (n == '1' && n2 == '3' && tentativo == 2)
		return ("4132");
	if (n == '1' && n2 == '3' && tentativo == 3)
		return ("4231");
	if (n == '1' && n2 == '2' && tentativo == 1)
		return ("4123");
	if (n == '1' && n2 == '2' && tentativo == 2)
		return ("4213");
	return ("f");
}

char	*inserimenti3(char n, char n2, int tentativo)
{
	if (n == '2' && n2 == '2' && tentativo == 1)
		return ("2143");
	if (n == '2' && n2 == '2' && tentativo == 2)
		return ("3142");
	if (n == '2' && n2 == '2' && tentativo == 3)
		return ("3412");
	if (n == '2' && n2 == '2' && tentativo == 4)
		return ("3241");
	if (n == '2' && n2 == '2' && tentativo == 5)
		return ("1423");
	if (n == '2' && n2 == '2' && tentativo == 6)
		return ("2413");
	return ("f");
}
