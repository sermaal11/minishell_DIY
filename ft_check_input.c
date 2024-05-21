/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/20 14:47:10 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_input(t_mini *mini, char *input, char **lines)
{
	mini->flags->quote = ft_check_quote(input, 2, 2, mini);
	mini->flags->pipe = ft_count_pipes(input);
	if (mini->flags->quote == 0 && mini->flags->pipe == 0)
		return (1);
	if (mini->flags->pipe != 0)
	{
		lines = ft_split_pipes(input);
		if (!lines)
			return (1);
		printf("%s\n", lines[0]);
	}
	// mini->flags->red = ft_count_redirect(mini, input);
	// if (mini->flags->red != 0)								/* CREAR FUNCION ft_count_redirect y ft_split_redirects */
	// 	lines = ft_split_redirects(mini, input);
	return (0);
}
