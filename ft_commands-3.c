/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands-3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:07:14 by user              #+#    #+#             */
/*   Updated: 2024/06/07 13:02:28 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nothing(char *input, int i)
{
	while (input[i] && i > 0 && input[i] != ' ')
		i--;
	if (i == 0)
		return (0);
	return (1);
}

int	ft_process_quotes(char *input, int *i, int *first)
{
	int	j;

	j = *i;
	while (input[*i] == 34 || input[*i] == 39)
		*i = ft_locate_next_quote(*i + 1, input, input[*i]) + 1;
	while (j++ < *i)
		(*first)++;
	return (*i);
}

int	ft_find_char(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}

void	ft_process_space(char *input, int *i, int *first, int *stop)
{
	if (input[*i] == ' ')
	{
		*first = 0;
		if (input[*i + 1] != ' ' && ft_nothing(input, *i) == 1)
			(*stop)--;
	}
}
