/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:18:43 by aanghi            #+#    #+#             */
/*   Updated: 2024/04/12 11:42:07 by aanghi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command_f_histori(char *input)
{
	HIST_ENTRY	*hist_entry;
	int			command_number;

	if (input[0] == '!')
	{
		command_number = ft_atoi(&input[1]);
		hist_entry = history_get(command_number);
		if (hist_entry != NULL)
		{
			free(input);
			input = hist_entry->line;
			free(hist_entry->line);
			printf("02: Give me a command, darling: %s\n", input);
		}
	}
	return (input);
}

static char	*controll_close_char(char *input, char c, int i, int i2)
{
	char	*s;

	while (input[i2] != '\0')
	{
		if (input[i2] == c && i == 0)
			i = 1;
		else if (input[i2] == c && i == 1)
			i = 0;
		if (input[i2] != '\0')
			i2++;
	}
	if (i == 1)
	{
		printf("02: Close the \' or \", darling: %s", input);
		s = ft_strjoin12f(input, readline(""));
		add_history(s);
	}
	else
		s = input;
	return (s);
}

char	*get_command_f_0(void)
{
	char	*input;
	char	*f;
	int		i;

	input = readline("02: Give me a command, darling: ");
	if (input == NULL)
		return (NULL);
	if (strlen(input) > 0)
		add_history(input);
	input = get_command_f_histori(input);
	input = controll_close_char(input, '\'', 0, 0);
	input = controll_close_char(input, '\"', 0, 0);
	i = skip(0, input);
	if (input[i] == '\0')
	{
		free(input);
		input = malloc(1);
		input[0] = '\0';
		return (input);
	}
	f = ft_strjoin(input, " ");
	free(input);
	return (f);
}
