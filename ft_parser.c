/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/05 19:15:11 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void process_lines(t_cmd **cmd, char **lines)
{
	t_cmd	*new_cmd;
	t_cmd	*current;
	int		i;

	i = 0;
	while (lines[i] != NULL)
	{
		new_cmd = ft_add_command(lines[i], -1);
		if (*cmd == NULL)
			*cmd = new_cmd;
		else
		{
			current = *cmd;
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
		*(cmd) = ft_add_command(input, -1);
	else
		process_lines(cmd, lines);

	(*cmd)->files = ft_calloc(sizeof(t_files), 1);
	(*cmd)->files->error = 0;
	ft_files(*(cmd), mini, (*cmd)->files);
	if ((*cmd)->files->error == -1)
		return (0);

	print_cmd(*cmd);
	// print_files((*cmd)->files);

	return (1);
}
