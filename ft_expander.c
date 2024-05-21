/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:28:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/20 10:57:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_craft_result(char *final_line, char *line, char *var, int c)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = -1;
	k = ft_search_next_char(line, '$', -1);
	if ((size_t)k == ft_strlen(line))
		return (line);
	while (++i < k)
		final_line[i] = line[i];
	while (var[++j])
		final_line[i + j] = var[j];
	while (line[i + c])
	{
		final_line[i + j] = line[i + c];
		i++;
	}
	final_line[i + j] = '\0';
	return (final_line);
}

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

char	*ft_change_name_var(char *line)
{
	int		i;
	int		j;
	char	*var_name;

	i = ft_locate_next_quote(0, line, '$') + 1;
	j = 0;
	while (line[i + j] && line[i + j] == ' ' && line[i + j] != '"' && line[i + j] != 39 && ft_check_special_char(line[i + j] == 0))
		j++;
	var_name = ft_calloc(sizeof(char), j + 1);
	if (!var_name)
		ft_exit_error("Malloc error", 16);
	j = 0;
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != '"' && line[i + j] != 39 && ft_check_special_char(line[i + j]) == 0)
	{
		var_name[j] = line[i + j];
		j++;
	}
	return (var_name);
}

char	*ft_change_var(t_cmd *cmd, char *line, char **var_reminder)
{
	char	*var_name;
	int		i;

	if (ft_strnstr(line, "$?", ft_strlen(line)) != 0)
		return (ft_replace_value_of_var(line));
	var_name = ft_change_name_var(line);
	i = ft_search_next_char(line, '$', -1);
	while (line[++i] && line[i] != ' ')
	{
		if ((ft_check_special_char(line[i]) == -1 && line[i] != '$')
			|| (line[i] == '$' && i == ft_search_next_char(line, '$', ft_search_next_char(line, '$', -1) + 1)))
		{
			*var_reminder = ft_split_var(line, i, cmd);
			break ;
		}
	}
	if (!var_name)
		return (NULL);
	if (var_name[0])
		return (ft_strchr(line, '$') + 1);
	return (ft_compare_var_name(cmd, line, var_name));
}

char	*ft_change_dollar_x_var(t_cmd *cmd, char *command, char *var_reminder)
{
	char	*temp;

	if (ft_check_dollar_n_digits(command, -1) == 0)
		command = ft_remove_dollar_n_digits(command, -1, -1);
	if (ft_locate_dollar(command) == 0)
		return (command);
	cmd->flags->dollar = 0;
	command = ft_change_var(cmd, command, &var_reminder);
	if (ft_locate_dollar(command) == 1)
		command = ft_change_dollar_x_var(cmd, command, NULL);
	if (cmd->flags->dollar == 1)
	{
		temp = ft_strjoin_custom(command, var_reminder, -1, -1);
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

void	ft_expander(t_cmd *cmd)
{
	int	i;

	i = -1;
	if (ft_locate_dollar(cmd->cmd) == 1)
		cmd->cmd = ft_change_dollar_x_var(cmd, cmd->cmd, NULL);
	if (ft_check_relative_home(cmd->cmd) == 1)
		cmd->cmd = ft_replace_home(cmd->cmd);
	if (!cmd->args)
		return ;
	while (cmd->args[++i])
	{
		if (ft_locate_dollar(cmd->args[i]) == 1)
			cmd->args[i] = ft_change_dollar_x_var(cmd, cmd->args[i], NULL);
		if (ft_check_relative_home(cmd->args[i]) == 1)
			cmd->args[i] = ft_replace_home(cmd->args[i]);
	}
}
