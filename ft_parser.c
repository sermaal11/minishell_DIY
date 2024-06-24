/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/24 08:59:47 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	// int		i;
	char	**lines;
	// t_cmd	*tmp;
	// i = 0;
	lines = NULL;
	if(ft_check_input(mini, input, &lines)) // Division de || y >> ajustar la &lines;
		return (0);
	// if (mini->flags->pipe == 0 && mini->flags->redirect->red_error != 0) // Poner "== 0" en la segunda
	*(cmd) = ft_add_command(mini, input);
	// else
	// 	*(cmd) = ft_add_command(mini, lines[0]);
	printf(B_CY_0"ARGS[0] --> %s\n"RESET, (*cmd)->args[0]);
	return (1);
	// while (++i <= mini->flags->pipe)
	// {
	// 	mini->char_amount = 0;
	// 	tmp = ft_add_command(mini, lines[i]);
	// 	ft_expander(&tmp);
	// 	(ft_last_command(cmd)->next = tmp);
	// }
	// while (i--)
	// 	free(lines[i]);
	// free(lines);
	// free(input);
	return (1);
}
