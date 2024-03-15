/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:14:29 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/15 18:23:56 by smarin-a         ###   ########.fr       */
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

// ! Prototipo de funcion para tokenizar
int	ft_strtokenize(char *input, t_mini *mini)
{
	printf(YE3"input --> %s, env --> %s\n"RESET, input, mini->env->env[0]);
	// Si la tokenizcion va bien, nos devuelve un 1.
	return (1);
}
