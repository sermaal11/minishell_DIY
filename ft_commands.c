/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:31:25 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/21 10:09:33 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_args(char *input)
{
	int	i;
	int	args_amount;

	i = -1;
	args_amount = 0;
	while (input[++i])
	{
		if ((input[i] != 32 && input[i] != 34 && input[i] != 39) && (input[i + 1] == 32 || input[i + 1] == '\0' || input[i +1] == 34 || input[i + 1] == 39))
			args_amount++;
		if (input[i] == 34 || input[i] == 39)
		{
			i = ft_locate_next_quote(i + 1, input, input[i]);
			if (input[i] == 34 || input[i] == 39)
				args_amount++;
		}
	}
	return (args_amount);
}

char	*ft_get_command(t_mini *mini, char *input)
{
	int		i;
	int		init;
	char	*command;

	i = -1;
	while (input[i] == 32 || (input[i] == 9 && input[i] <= 13))
		i++;
	init = i + 1;
	while (input[++i] && input[i] != 32 && !(input[i] >= 9 && input[i] <= 13) && !ft_is_not_mayor_n_minor_char(input[i]))
	{
		if (input[i] == 34 || input[i] == 39)
			i = ft_locate_next_quote(i + 1, input, input[i]);
	}
	if (i && !ft_is_not_mayor_n_minor_char(input[i]))
		command = ft_substr(input, init, i);
	else
		command = ft_strdup("CD");
	mini->char_amount += i;
	printf("COMMAND %s\n", command);
	return (command);
}

t_cmd	*ft_add_command(t_mini *mini, char *input)
{
	t_cmd	*new_cmd;

	printf("INPUT = %s\n", input);
	new_cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!new_cmd)
		ft_exit_error("Malloc error", 9);
	new_cmd->cmd = ft_get_command(mini, input + mini->char_amount);
	printf("COMMAND2 %s\n", new_cmd->cmd);
	new_cmd->args_amount = ft_count_args(input + mini->char_amount);
	printf("AMOUNT %d\n", new_cmd->args_amount);
	new_cmd->next = NULL;
	new_cmd->flags = mini->flags;
	new_cmd->env = mini->env;
	if (new_cmd->args_amount == 0)
		return (new_cmd);
	new_cmd->args = ft_get_args(input, new_cmd->args_amount);
	for (int i = 0; i < new_cmd->args_amount + 1; i++)
		printf("%s\n", new_cmd->args[i]);
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
		ft_exit_error("Malloc error", 17);
	i = 0;
	while (line[j])
		res[i++] = line[j++];
	res[i] = '\0';
	return (res);
}