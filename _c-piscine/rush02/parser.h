/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apuddu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 20:34:23 by apuddu            #+#    #+#             */
/*   Updated: 2023/11/12 21:46:40 by apuddu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "delete_lines.h"
# include "string.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_realloc(char *buf, int buf_size, int new_size);
int		index_of(char **arr, int sz_arr, char *str);
char	**get_keys(void);
ssize_t	ft_getline(int fd, char **dest, int *eof);
void	get_keys2(char **keys);
void	parse_line(int fd, int *eof, char **keys, char **values);
char	**parse_values(char *filename);
void	get_keys2(char **keys);

char	**get_keys(void)
{
	char	**keys;

	keys = (char **)malloc(42 * sizeof(char *));
	keys[0] = "";
	keys[1] = "1";
	keys[2] = "2";
	keys[3] = "3";
	keys[4] = "4";
	keys[5] = "5";
	keys[6] = "6";
	keys[7] = "7";
	keys[8] = "8";
	keys[9] = "9";
	keys[10] = "10";
	keys[11] = "11";
	keys[12] = "12";
	keys[13] = "13";
	keys[14] = "14";
	keys[15] = "15";
	keys[16] = "16";
	get_keys2(keys);
	return (keys);
}

void	get_keys2(char **keys)
{
	keys[17] = "17";
	keys[18] = "18";
	keys[19] = "19";
	keys[20] = "20";
	keys[21] = "30";
	keys[22] = "40";
	keys[23] = "50";
	keys[24] = "60";
	keys[25] = "70";
	keys[26] = "80";
	keys[27] = "90";
	keys[28] = "100";
	keys[29] = "**";
	keys[30] = "1000";
	keys[31] = "1000000";
	keys[32] = "1000000000";
	keys[33] = "1000000000000";
	keys[34] = "1000000000000000";
	keys[35] = "1000000000000000000";
	keys[36] = "1000000000000000000000";
	keys[37] = "1000000000000000000000000";
	keys[38] = "1000000000000000000000000000";
	keys[39] = "1000000000000000000000000000000";
	keys[40] = "1000000000000000000000000000000000";
	keys[41] = "1000000000000000000000000000000000000";
}

// returns index of str in arr (-1 if str is not in arr)
int	index_of(char **arr, int sz_arr, char *str)
{
	int	i;

	i = 0;
	while (i < sz_arr)
	{
		if (streq(arr[i], str))
			return (i);
		i++;
	}
	return (-1);
}

void	parse_line(int fd, int *eof, char **keys, char **values)
{
	char	*s2;
	char	*str;
	int		ind;

	ft_getline(fd, &str, eof);
	s2 = split(str, ':');
	if (s2)
	{
		ind = index_of(keys, 42, clean_str(str));
		if (ind != -1)
			values[ind] = ft_strcpy(strip(s2));
	}
	free(str);
}

char	**parse_values(char *filename)
{
	int		fd;
	char	**values;
	int		eof;
	char	**keys;

	values = (char **)malloc(42 * sizeof(char *));
	values[29] = "";
	keys = get_keys();
	eof = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	while (!eof)
	{
		parse_line(fd, &eof, keys, values);
	}
	close(fd);
	delete_lines(keys, values);
	return (values);
}

#endif
