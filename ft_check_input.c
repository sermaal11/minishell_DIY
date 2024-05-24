/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/24 17:01:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_start_red(t_mini *mini)
{
	mini->flags->redirect = (t_red *)malloc(sizeof(t_red));
	mini->flags->redirect->error = (char *)malloc(sizeof(char *) * 3);
	ft_bzero(mini->flags->redirect->error, 3);
	mini->flags->redirect->red_error = 0;
	mini->flags->redirect->si_le = 0;
	mini->flags->redirect->si_ri = 0;
	mini->flags->redirect->do_le = 0;
	mini->flags->redirect->do_ri = 0;
}

int	ft_count_redirect(t_mini *mini, char *input)
{
	int	i;

	i = 0;
	ft_start_red(mini);
	while (input[i] != '\0')
	{
		if (input[i] == '>')
		{
			mini->flags->redirect->si_le += 1;
			if (input[i - 1] && input[i - 1] == '>')
			{
				mini->flags->redirect->do_le += 1;
				mini->flags->redirect->si_le -= 2;
			}
			if (input[i - 1] && input[i - 1] == '<')
			{
				mini->flags->redirect->red_error = 1;
				mini->flags->redirect->error[0] = input[i - 1];
				mini->flags->redirect->error[1] = input[i];
				break;
			}
			if (input[i - 2] && (input[i - 2] == '>' || input[i - 2] == '<'))
			{
				mini->flags->redirect->red_error = 3;
				mini->flags->redirect->error[0] = input[i];
			}
			if (input[i - 3] && (input[i - 3] == '>' || input[i - 3] == '<'))
			{
				mini->flags->redirect->red_error = 4;
				mini->flags->redirect->error[0] = input[i - 1];
				mini->flags->redirect->error[1] = input[i];
			}
		}
		if (input[i] == '<')
		{
			mini->flags->redirect->si_ri += 1;
			if (input[i - 1] && input[i - 1] == '<')
			{
				mini->flags->redirect->do_ri += 1;
				mini->flags->redirect->si_ri -= 2;
			}
			if (input[i - 1] && input[i - 1] == '>')
			{
				mini->flags->redirect->red_error = 2;
				mini->flags->redirect->error[0] = input[i];
				if (input[i + 1] && (input[i + 1] == '>' || input[i + 1] == '>'))
				{
					mini->flags->redirect->error[0] = input[i];
					mini->flags->redirect->error[1] = input[i + 1];
					break ;
				}
					
			}
			if (input[i - 2] && (input[i - 2] == '<' || input[i - 2] == '>'))
			{
				mini->flags->redirect->red_error = 3;
				mini->flags->redirect->error[0] = input[i];
			}
			if (input[i - 3] && (input[i - 3] == '<' || input[i - 3] == '>'))
			{
				mini->flags->redirect->red_error = 4;
				mini->flags->redirect->error[0] = input[i - 1];
				mini->flags->redirect->error[1] = input[i];
			}
			
		}
		i++;
	}
	printf("mini->flags->redirect->si_le = %d\n", mini->flags->redirect->si_le);
    printf("mini->flags->redirect->si_ri = %d\n", mini->flags->redirect->si_ri);
    printf("mini->flags->redirect->do_le = %d\n", mini->flags->redirect->do_le);
    printf("mini->flags->redirect->do_ri = %d\n", mini->flags->redirect->do_ri);
    printf("mini->flags->redirect->red_error = %d\n", mini->flags->redirect->red_error);
    printf("mini->flags->redirect->error = %s\n", mini->flags->redirect->error);
	return (0);
}

// ERRORES

// 1 = <>
// 2 = <
// 3 = > o <
// 4 = << o >>

int	ft_check_input(t_mini *mini, char *input, char ***lines)
{
	mini->flags->quote = ft_check_quote(input, 2, 2, mini);
	mini->flags->pipe = ft_count_pipes(input);
	mini->flags->red = ft_count_redirect(mini, input);
	// if (mini->flags->red != 0)
	// {
	// 	printf("DL = %d\n", mini->flags->redirect->do_le);
	// 	printf("DR = %d\n", mini->flags->redirect->do_ri);
	// 	printf("SL = %d\n", mini->flags->redirect->si_le);
	// 	printf("SR = %d\n", mini->flags->redirect->si_ri);
	// }
	if (mini->flags->quote == 0 && mini->flags->pipe == 0)
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
