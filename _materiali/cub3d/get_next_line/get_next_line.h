/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfrancav & pfalasch <lfrancav@student.4    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 15:41:42 by ccolaiac          #+#    #+#             */
/*   Updated: 2024/03/08 18:10:43 by lfrancav &       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 1

char	*get_next_line(int fd);
char	*ft_gnl_strdup(const char *s1);
char	*ft_gnl_strjoin(char *s1, char *s2);
int		ft_search(const char *s, char c);
char	*ft_gnl_substr(char *s, unsigned int start, size_t len, int need_free);
int		ft_line(char *src);

#endif
