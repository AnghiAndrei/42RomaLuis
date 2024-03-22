/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:52:53 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/07 13:06:46 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "get_next_line.h"

char	**get_args(char *s);
void	controll2(char **m);
void	here_doc(char *rule);
char	*gu3(int *i, char *s);
int		controll_in(char *file);
char	*ricerca_path(char **envp);
void	child(char *cmd, char *path);
int		ft_strlen(const char *string);
void	controll1(int *fd, pid_t *pid);
char	*gu2(int *i, char *s, char ch);
char	**ft_split(char const *s, char c);
int		controll_out(char *file, char *here_doc);
char	*program_name(char *command, char *path);
void	gu1(int *word, char *s, int *i, char ch);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
