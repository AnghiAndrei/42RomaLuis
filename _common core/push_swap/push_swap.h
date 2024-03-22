/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:17:41 by aanghi            #+#    #+#             */
/*   Updated: 2024/02/26 17:06:49 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "get_next_line.h"

typedef struct s_stack
{
	int				data;
	struct s_stack	*next;
}				t_stack;

int		quick_sort_b(t_stack **stack_a, t_stack **stack_b, int n_r, int len);
int		quick_sort_a(t_stack **stack_a, t_stack **stack_b, int n_r, int len);
void	sort3(t_stack **stack, t_stack *p, t_stack *s, t_stack *t);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	fill_stack(t_stack **stack, int argc, char **argv, int i);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
void	rr_rrr(t_stack **stack_a, t_stack **stack_b, int r);
void	quick_sort_3_a_b(t_stack **a, t_stack **b, int len);
void	push(t_stack **stack_a, t_stack **stack_b, char c);
int		get_pivot(t_stack *stack, int len, int *pivot);
void	ft_lstadd_back(t_stack **lst, t_stack *new);
void	sort_3_b(t_stack **a, t_stack **b, int len);
int		check_sorted_des(t_stack *stack, int len);
int		check_sorted_asc(t_stack *stack, int len);
void	rrotate(t_stack **stack, char *c, int s);
void	rotate(t_stack **stack, char *c, int s);
void	controll1(t_stack **stack, int number);
void	swap(t_stack **stack, char *c, int s);
void	sort(t_stack **a, t_stack **stack_b);
void	bubble_sort(int *stack_c, int len);
char	**ft_split(char const *s, char c);
void	ceck_input(int argc, char **argv);
int		ft_strlen(const char *string);
int		ft_atoi(const char *string);
char	*get_next_line(int fd);
int		ft_lstlen(t_stack *lst);
void	error_message(void);
void	ft_putstr(char *s);
