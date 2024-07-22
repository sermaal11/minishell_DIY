/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/20 16:57:14 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_move_files(t_cmd *cmd, t_mini *mini)
{
	cmd->files = ft_calloc(sizeof(t_files), 1);
	cmd->files->error = 0;
	if (mini->flags->redirect && mini->flags->redirect->number != 0)
		ft_files(cmd, mini, cmd->files);
}

void	process_lines(t_cmd **cmd, t_mini *mini, char **lines, int i)
{
	t_cmd	*new_cmd;
	t_cmd	*current;

	while (lines && lines[i] != NULL)
	{
		new_cmd = ft_add_command(lines[i++], -1);
		if (*cmd == NULL)
			*cmd = new_cmd;
		else
		{
			current = *cmd;
			while (current->next != NULL)
				current = current->next;
			current->next = new_cmd;
		}
		ft_move_files(new_cmd, mini);
		if (mini->cmd->files->error == -1)
			return ;
	}
}

char	**ft_strstr_expander(t_mini *mini, char **args)
{
	char	**tmp;
	char	**result;
	int		size;
	int		i;
	
	i = -1;
	size = ft_strstr_len(args);
	tmp = ft_strstr_dup(args);
	ft_strstr_free(args);
	result = ft_calloc(sizeof(char *), size + 1);
	if (result == NULL)
	{
		ft_strstr_free(tmp);
		return (NULL);
	}
	while (tmp[++i])
	{
		result[i] = ft_expander(mini->env->env, tmp[i]);
		free(tmp[i]);
	}
	free(tmp);
	ft_strstr_printf(result);
	
	return (result);
}

void	ft_do_expander(t_mini *mini, t_cmd *cmd)
{
	t_cmd	*current;
	int		i;

	i = 0;
	current = cmd;
	while (current != NULL)
	{
		printf("\nI = %d\n", i);
		// printf("ARGS\n");
		if (current->args)
		{
			// ft_strstr_printf(current->args);
			current->args = ft_strstr_expander(mini, current->args);
			// ft_strstr_printf(current->args);
		}
		// printf("\nF_ORDER\n");
		// if (current->files->f_order)
		// 	ft_strstr_printf(current->files->f_order);
		// printf("\nORDER\n");
		// if (current->files->order)
		// 	ft_strstr_printf(current->files->order);
		current = current->next;
		i++;
	}
}

int	ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	char	**lines;

	lines = ft_check_input(mini, input);
	if (mini->flags->pipe == -1 || mini->flags->quote == -1 || mini->flags->locate_red == -1)
		return (0);
	else if (mini->flags->pipe == 0)
	{
		*(cmd) = ft_add_command(input, -1);
		ft_move_files(*(cmd), mini);
	}
	else
		process_lines(cmd, mini, lines, 0);
	ft_strstr_free(lines);
	if (mini->cmd->files->error == -1)
		return (0);
	ft_do_expander(mini, *cmd);
	// EXPANDER
	// "QUOTES'
	// COMMANDS
	print_cmd(*cmd);
	return (1);
}
