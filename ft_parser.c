/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/27 12:52:29 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	char	**lines = NULL;
	int		i;
	
	i = -1;
	lines = ft_check_input(mini, input);
	if (mini->flags->pipe == -1 || mini->flags->quote == -1 || mini->flags->locate_red == -1)
		return (0);
	else if (mini->flags->pipe == 0)
		*(cmd) = ft_add_command(mini, input);
	else
	{
		while (lines[++i])
		{
			t_cmd *new_cmd = ft_add_command(mini, lines[i]);
			if (*cmd == NULL)
				*cmd = new_cmd;
			else
			{
				t_cmd *current = *cmd;
				while (current->next != NULL)
					current = current->next;
				current->next = new_cmd;
			}
			free(lines[i]);
		}
		if (lines)
			free(lines);
	}
	return (1);
}
