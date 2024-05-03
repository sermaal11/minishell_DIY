/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:28:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/03 13:08:47 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_locate_dollar(char *cmd)
{
	int	i;
	int	double_quote;

	i = 0;
	double_quote = 1;
	while (cmd[i])
	{
		if (cmd[i] == 39 && double_quote == 1)
			i = ft_locate_next_quote(i + 1, cmd, cmd[i]);
		if (cmd[i] == 34)
			double_quote *= -1;
		if (cmd[i] == '$' && cmd[i + 1] && cmd[i + 1] != ' ')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_change_var(t_cmd *cmd, char *line, char **var_reminder)
{
	char	*var_name;
	int		i;

	if (ft_strnstr(line, "$?", ft_strlen(line)) != 0)
		return (ft_replace_value_of_var(line));
}

char	*ft_change_dollar_x_var(t_cmd *cmd, char *command, char *var_reminder)
{
	char	*temp;

	if (ft_check_dollar_n_ditis(command) == 0)
		command = ft_remove_dollar_n_digits(command, -1, -1);
	if (ft_locate_dollar(command) == 0)
		return (command);
	cmd->flags->dollar = 0;
	command = ft_change_var(cmd, command, &var_reminder);
	if (ft_locate_dollar(command) == 1)
		command = ft_change_dollar_x_var(cmd, command, NULL);
	if (cmd->flags->dollar == 1)
	{
		temp = ft_strjoin_custom(command, var_reminder, 0, 0);
		free(command);
		command = temp;
		free(var_reminder);
		var_reminder = NULL;
		cmd->flags->dollar = 0;
	}
	if (ft_locate_dollar(command) == 1)
		return (ft_change_dollar_x_var(cmd, command, NULL));
	if (var_reminder)
		free(var_reminder);
	return (command);	
}

void	ft_expander(t_cmd **cmd)
{
	int	i;
	
	i = -1;
	if (ft_locate_dollar((*cmd)->cmd) == 1)
		(*cmd)->cmd = ft_change_dollar_x_var((*cmd), (*cmd)->cmd, NULL);
	if (ft_check_relative_home((*cmd)->cmd) == 1)
		(*cmd)->cmd = ft_replace_home((*cmd)->cmd);
	if (!(*cmd)->args)
		return ;
	while((*cmd)->args[++i])
	{
		if (ft_locate_dollar((*cmd)->args[i]) == 1)
			(*cmd)->args[i] = ft_change_dollar_x_var((*cmd), (*cmd)->args[i], NULL);
		if (ft_check_relative_home((*cmd)->args[i]) == 1)
			(*cmd)->args[i] = ft_replace_home((*cmd)->args[i]);
	}
}
