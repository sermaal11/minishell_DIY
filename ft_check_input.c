/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/06/25 17:17:31 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_check_input(t_mini *mini, char *input)
{
	char	**lines;
	
	mini->flags->locate_red = ft_count_redirect(mini, input);
	mini->flags->quote = ft_check_quote(input, 2, 2, mini);
	mini->flags->pipe = ft_count_pipes(input);
	if (mini->flags->quote == 0 && mini->flags->pipe == 0 && mini->flags->redirect->red_error == 0)
		return (NULL);
	if (mini->flags->pipe > 0)
	{
		lines = ft_split(input, '|');
		if (*(lines) == NULL)
			return (NULL);
	}
	if (mini->flags->pipe == -1 || mini->flags->quote == -1 || mini->flags->locate_red == -1)
		return (NULL);
	// 	(*lines) = ft_split_redirects(mini, input);
	return (lines);
}

