/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/01 18:26:22 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_input(t_mini **mini, char *input, char ***lines)
{
	(*mini)->flags->quote = ft_check_quote(input, 2 ,2, (*mini));
	if ((*mini)->flags->quote == 0)
	{
		free(input);
		return (1);
	}
	(*mini)->flags->pipe = ft_count_pipes(input);
	if ((*mini)->flags->pipe == -1)
	{
		free(input);
		return (1);
	}
	*lines = ft_split_pipes(input);
	if (!(*lines))
	{
		free(input);
		return (1);
	}
	return (0);
}