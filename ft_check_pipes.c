/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:22:30 by smarin-a          #+#    #+#             */
/*   Updated: 2024/06/05 16:01:31 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_fill_matrix_pipes(char *input, char **splited_pipes_matrix)
{
	int	i;
	int	init;
	int	position;

	i = -1;
	init = 0;
	position = 0;
	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
			i = ft_locate_next_quote(i + 1, input, input[i]);
		if ((input[i + 1] == '|' || input[i + 1] == '\0') && input[i] != '|')
		{
			splited_pipes_matrix[position] = ft_substr(input, init, i - init + 1);
			if (splited_pipes_matrix[position] == NULL)
				ft_exit_error(NULL, "Malloc error", 54);
			position++;
		}
		if (input[i] == '|' && (input[i + 1] != '|' || input[i + 1] != '\0'))
			init = i + 1;
		splited_pipes_matrix[position] = NULL;
		return (splited_pipes_matrix);
	}
	return (NULL);
}

int	ft_count_pipes(char *input)
{
	int	i;
	int	amount;

	i = -1;
	amount = 0;
	while (input[++i])
	{
		if (input[i] == 34 || input[i] == 39)
			i = ft_locate_next_quote(i + 1, input, input[i]);
		if ((input[i] == '|' && (input[i + 1] == '|' || input[i + 1] == '\0'))
			|| input[0] == '|')
		{
			ft_put_error("bash", NULL, "syntax error near unexpected token `||'");
			g_exit_status = 258;
			return (-1);
		}
		if (input[i] == '|')
			amount++;
	}
	return (amount);
}

int	ft_check_pipes_arg(char *input)
{
	int	i;
	int	result;

	i = -1;
	result = -1;
	printf("A%s\n", input);
	while (input[++i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			result = 0;
	}
	printf("%d\n", result);
	if (result == -1)
		ft_put_error("bash", NULL, "syntax error near unexpected token `|'");
	return (result);
}

char	**ft_split_pipes(char *input)
{
	char	**splited_pipes_matrix;
	int		i;

	i = -1;
	splited_pipes_matrix = (char **)malloc(sizeof(char **) * (ft_count_pipes(input) + 2));
	if (!splited_pipes_matrix)
		ft_exit_error(NULL, "Malloc error", 54);
	splited_pipes_matrix = ft_fill_matrix_pipes(input, splited_pipes_matrix);
	while (splited_pipes_matrix[++i])
	{
		if (ft_check_pipes_arg(splited_pipes_matrix[i]) == -1)
		{
			g_exit_status = 258;
			while (i >= 0)
				free(splited_pipes_matrix[i--]);
			free(splited_pipes_matrix);
			return (NULL);
		}
	}
	return (splited_pipes_matrix);
}
