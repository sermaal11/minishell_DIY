/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/03 11:47:03 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void process_lines(t_cmd **cmd, char **lines)
{
	int i = 0;

	while (lines[i] != NULL)
	{
		t_cmd *new_cmd = ft_add_command(lines[i]);
		if (*cmd == NULL)
			*cmd = new_cmd;
		else
		{
			t_cmd *current = *cmd;
			while (current->next != NULL)
				current = current->next;
			current->next = new_cmd;
		}
		free(lines[i++]);
	}
	if (lines != NULL)
		free(lines);
}

int	ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	char	**lines = NULL;
	
	lines = ft_check_input(mini, input);
	if (mini->flags->pipe == -1 || mini->flags->quote == -1 || mini->flags->locate_red == -1)
		return (0);
	else if (mini->flags->pipe == 0)
		*(cmd) = ft_add_command(input);
	else
		process_lines(cmd, lines);
	return (1);
}
