/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/06/09 12:49:49 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_input(t_mini *mini, char *input, char ***lines)
{
	mini->flags->quote = ft_check_quote(input, 2, 2, mini);
	mini->flags->pipe = ft_count_pipes(input);
	mini->flags->locate_red = ft_count_redirect(mini, input);
	if (mini->flags->redirect->red_error != 0)
	{
		if (mini->flags->redirect->red_error < 3)
		{
			if (mini->flags->redirect->red_error == 1)
				mini->flags->redirect->error = ft_substr(input, 1 + mini->flags->locate_red, 1);
			else if ((mini->flags->redirect->red_error == 2))
				mini->flags->redirect->error = ft_substr(input, 2 + mini->flags->locate_red, 1);
		}
		else if (mini->flags->redirect->red_error > 2)
		{
			if (mini->flags->redirect->red_error == 3)
				mini->flags->redirect->error = ft_substr(input, 1 + mini->flags->locate_red, 2);
			else if ((mini->flags->redirect->red_error == 4))
				mini->flags->redirect->error = ft_substr(input, 2 + mini->flags->locate_red, 2);
		}
		printf("mini: parse error near `%s'\n", mini->flags->redirect->error);
		free(mini->flags->redirect->error);
		mini->flags->redirect->error = NULL;
		return (0);
	}
	if (mini->flags->quote == 0 && mini->flags->pipe == 0 && mini->flags->redirect->red_error == 0)
		return (1);
	if (mini->flags->pipe != 0)
	{
		// (*lines) = ft_split_pipes(input);
		if (lines == NULL)
			return (1);
	}
	// if (mini->flags->red != 0)								/* CREAR FUNCION ft_count_redirect y ft_split_redirects */
	// 	(*lines) = ft_split_redirects(mini, input);
	return (0);
}
