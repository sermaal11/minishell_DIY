/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/21 10:38:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	ft_strtok(t_mini *mini, t_cmd *cmd, char *input)
{
	// int		i;
	char	**lines;
	// t_cmd	*tmp;
	// i = 0;
	lines = NULL;
	mini->char_amount = 0;
	if(ft_check_input(&mini, input, &lines))
		return (0);
	printf("AAA\n");
	printf("S = %s\n", input);
	if (mini->flags->pipe == 0) //Anadir mini->flags->red == -1
		cmd = ft_add_command(mini, input);
	else
		cmd = ft_add_command(mini, lines[0]);
	return (1);
	printf("a%s\n", cmd->args[0]);
	// printCmd(cmd);
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
