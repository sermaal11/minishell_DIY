/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:14:29 by smarin-a          #+#    #+#             */
/*   Updated: 2024/04/30 12:36:27 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_void_input(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
		j = j + ft_isspace(input[i++]);
	if (j == i)
		return (-1);
	return (0);
}
