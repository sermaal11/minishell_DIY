/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:22:30 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/01 19:39:25 by smarin-a         ###   ########.fr       */
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
				ft_exit_error("Malloc error", 54);
			position++;
		}
		if (input[i] == '|' && (input[i + 1] != '|' || input[i + 1] != '\0'))
			init = i + 1;
		splited_pipes_matrix[position] = NULL;
		return (splited_pipes_matrix);
	}
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
			ft_put_error("bash", NULL, "syntax error near unexpected token `|'");
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
	while (input[++i])
	{
		if (input[i] != ' ' && input[i] != '\t' && input[i] != '\n')
			result = 0;
	}
	if (result == -1)
		ft_put_error("bash", NULL, "syntax error near unexpected token `|'");
	return (result);
}

char	**ft_split_pipes(char *input)
{
	char	**splited_pipes_matrix;
	int		i;

	i = -1;
	splited_pipes_matrix = ft_calloc(sizeof(char *), (ft_count_pipes(input) + 2));
	if (!splited_pipes_matrix)
		ft_exit_error("Malloc error", 54);
	splited_pipes_matrix = ft_fill_matrix_pipes(input, splited_pipes_matrix);
	while (splited_pipes_matrix[++i])
	{
		if (ft_check_pipes_arg(splited_pipes_matrix[i]) == -1
			|| ft_check_redir_arg(splited_pipes_matrix, i) == -1)
		{
			// Seguir desde https://github.com/gemartin99/Minishell/blob/master/src/utils_pipes.c#L113
			// ft_check_redir_arg(splited_pipes_matrix, i); = check_redir_arg en GEmartin		
		}
	}
}