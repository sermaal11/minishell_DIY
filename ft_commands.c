/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:31:25 by smarin-a          #+#    #+#             */
/*   Updated: 2024/06/27 11:34:37 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(char *input)
{
	int	i;
	int	args_amount;

	i = 0;
	args_amount = 0;
	// printf(PURPLE"CHAR = %c\n"RESET, input[i - 1]);
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		if ((input[i] != 32 && input[i] != 34 && input[i] != 39) && (input[i + 1] == 32 || input[i + 1] == '\0' || input[i +1] == 34 || input[i + 1] == 39))
			args_amount++;
		if (input[i] == 34 || input[i] == 39)
		{
			i = ft_locate_next_quote(i + 1, input, input[i]);
			if (input[i] == 34 || input[i] == 39)
				args_amount++;
		}
		i++;
	}
	return (args_amount);
}

char	*ft_get_command(t_mini *mini, char *input)
{
	int		i;
	int		init;
	char	*command;

	i = 0;
	while (input[i] == 32 || (input[i] == 9 && input[i] <= 13))
		i++;
	init = i + 1;
	while (input[i] && input[i] != 32 && !(input[i] >= 9 && input[i] <= 13) && !ft_is_not_mayor_n_minor_char(input[i]))
	{
		if (input[i] == 34 || input[i] == 39)
			i = ft_locate_next_quote(i + 1, input, input[i]);
		i++;
	}
	if (i && !ft_is_not_mayor_n_minor_char(input[i]))
	{
		command = ft_substr(input, init, i);
		if (command == NULL)
			ft_exit_error(NULL, "Malloc error", 50);
	}
	else
	{
		command = ft_strdup("CD");
		if (!command)
			ft_exit_error(NULL, "Malloc error", 50);
	}
	return (command);
	printf("%d\n", mini->flags->dollar);
}

t_cmd	*ft_add_command(t_mini *mini, char *input)
{
	t_cmd	*new_cmd;

	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		ft_exit_error(NULL, "Calloc error", 9);
	new_cmd->cmd = ft_get_command(mini, input);
	new_cmd->args_amount = ft_count_args(input);
	new_cmd->next = NULL;
	new_cmd->flags = mini->flags;
	new_cmd->env = mini->env;
	if (new_cmd->args_amount == 0)
		return (new_cmd);
	// printf("%s\n", input);
	ft_get_args(input, new_cmd->args_amount, &new_cmd->args);
	// int i = 0;
	// while (new_cmd->args[i] != NULL && i < new_cmd->args_amount)
	// 	printf("%s\n", new_cmd->args[i++]);
	return (new_cmd);
}

t_cmd	*ft_last_command(t_cmd **cmd)
{
	t_cmd	*temp;

	temp = *cmd;
	while (temp->next)
		temp = temp->next;
	return (temp);
}

char	*ft_split_var(char *line, int i, t_cmd *cmd)
{
	char	*res;
	int		j;

	cmd->flags->dollar = 1;
	j = 1;
	while (line[i])
		i++;
	res = malloc(sizeof(char) * i - j + 1);
	if (!res)
		ft_exit_error(NULL, "Malloc error", 17);
	i = 0;
	while (line[j])
		res[i++] = line[j++];
	res[i] = '\0';
	return (res);
}
