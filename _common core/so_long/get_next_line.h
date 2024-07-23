/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:25:54 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/07 18:26:33 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int		findn(char *buffer);
char	*get_next_line(int fd);
int		ft_strlen(const char *string);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strcpy(char *dest, char *src);
#endif
