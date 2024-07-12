/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/12 17:06:15 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	ft_strstr_red(char **input)
// {
// 	int	i;

// 	i = 0;
// 	if (input)
// 	{
// 		while (input[i])
// 		{
			
// 		} 
// 	}
// }

char	**ft_count_rp(t_mini *mini)
{
	char	**str = NULL;
	int		pipe;
	int		count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	pipe = 0;
	count = 0;
	while (mini->input[i] != '\0')
	{
		if (mini->input[i] == '\'' || mini->input[i] == '\"')
			i = ft_locate_next_quote(i + 1, mini->input, mini->input[i]);
		if (mini->input[i] == '>' && mini->input[i + 1] && mini->input[i + 1] == '|')
			count++;
		i++;
	}
	if (count > 0)
	{
		str = (char **)ft_calloc(sizeof(char *), count + 1);
		j = 0;
		i = 0;
		while (mini->input[i] != '\0')
		{
			if (mini->input[i] == '\'' || mini->input[i] == '\"')
				i = ft_locate_next_quote(i + 1, mini->input, mini->input[i]);
			if (mini->input[i] == '|')
				pipe++;
			if (mini->input[i] == '>' && mini->input[i + 1] && mini->input[i + 1] == '|' && j < count)
				str[j++] = ft_itoa(pipe);
			i++;
		}
	}
	return (str);
}

int process_lines(t_cmd **cmd, t_mini *mini, char **lines)
{
	t_cmd	*new_cmd;
	t_cmd	*current;
	// char	*red;
	int		exp;
	int		i;

	i = 0;
	exp = 0;
	while (lines && lines[i] != NULL)
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
		new_cmd->files = ft_calloc(sizeof(t_files), 1);
		new_cmd->files->error = 0;
		printf(B_PR_0"%s\n"RESET, lines[i]);
		if (lines[i + 1] != NULL)
			printf(B_GR_0"%s\n"RESET, lines[i + 1]);
		if (mini->flags->redirect)
			printf(B_CY_0"%d\n"RESET, mini->flags->redirect->number);
		new_cmd->files->exp = ft_count_rp(mini);
		if (new_cmd->files->exp)
		{
			int k = 0;
			while (new_cmd->files->exp[k])
				printf(B_YE_0"%s\n"RESET, new_cmd->files->exp[k++]);
		}
		if (new_cmd->files->exp)
		{
			if (new_cmd->files->exp[exp] && i == ft_atoi(new_cmd->files->exp[exp]))
			{
				ft_files(new_cmd, mini, new_cmd->files, 1);
				exp++;
			}
		}
		else
			ft_files(new_cmd, mini, new_cmd->files, 0);
		// printf("%d\n", new_cmd->files->exp);
		// if (mini->flags->redirect->number > 0)
		// {
		// 	red = ft_strchr(lines[i], '>');
		// 	if (red != NULL && ft_nothing(red, 0) == 1)
		// 	{
		// 		new_cmd->files->error = -2;
		// 		free(red);
		// 	}
		// }
			
		// if (mini->flags->redirect && mini->flags->redirect->number != 0)
		// if (ft_strstr_red(new_cmd->args) == 1)
		
			
		if (new_cmd->files->error == -1)
			return (-1);
		free(lines[i++]);
	}
	if (lines != NULL)
		free(lines);
	return (0);
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
		(*cmd)->files = ft_calloc(sizeof(t_files), 1);
		(*cmd)->files->error = 0;
		if (mini->flags->redirect && mini->flags->redirect->number != 0)
			ft_files(*(cmd), mini, (*cmd)->files, 0); // Añadir lo del otro lado y modificar el 0 por 1 o 0;
		if ((*cmd)->files->error == -1)
			return (0);
	}
	else
	{
		if (process_lines(cmd, mini, lines) == -1)
			// FREE_LINES
			return (0);
	}
	print_cmd(*cmd);

	// free((*cmd)->files);
	// print_files((*cmd)->files);

	return (1);
}
