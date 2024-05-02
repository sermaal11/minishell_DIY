/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 11:48:53 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/02 12:25:23 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_not_mayor_n_minor_char(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

char	ft_type_of_operator_char(int n)
{
	if (n == 1 || n == 2 || n == 5 || n == 6)
		return ('>');
	else if (n == 3 || n == 4)
		return ('<');
	return (0);
}