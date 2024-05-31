/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/31 10:01:53 by user             ###   ########.fr       */
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
	if(ft_check_input(mini, input, &lines)) // Revisar la division de pipes y crear division de referencias
		return (0);
	if (mini->flags->pipe == 0 && mini->flags->red == 0) 
		*(cmd) = ft_add_command(mini, input);
	else
		*(cmd) = ft_add_command(mini, lines[0]);
	return (1);
	free_t_cmd(cmd);
	// printf("%d\n", cmd->flags->dollar);
	// ft_expander(cmd);
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
