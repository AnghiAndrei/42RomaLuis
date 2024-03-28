/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_input.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:18:43 by aanghi            #+#    #+#             */
/*   Updated: 2024/03/28 10:22:50 by aanghi           ###   ########.fr       */
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
	char	*d;

	while (input[++i2] != '\0')
	{
		if (input[i2] == c && i == 0)
			i = 1;
		else if (input[i2] == c && i == 1)
			i = 0;
	}
	if (i == 1)
	{
		printf("02: Close the \' or \", darling: %s", input);
		d = readline("");
		s = ft_strjoin(input, d);
		free(d);
		add_history(s);
		free(input);
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
	input = controll_close_char(input, '\'', 0, -1);
	input = controll_close_char(input, '\"', 0, -1);
	i = skip(0, input);
	if (input[i] == '\0')
	{
		free(input);
		input = malloc(1);
		input[0] = '\0';
	}
	f = ft_strjoin(input, " ");
	free(input);
	return (f);
}
