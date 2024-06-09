/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:04:30 by smarin-a          #+#    #+#             */
/*   Updated: 2024/06/05 16:03:09 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_custom(char *str1, char *str2, size_t i, size_t c)
{
	char	*str;
	size_t	size1;

	size1 = ft_strlen(str1);
	if (str1[size1 -1] == 34 || str1[size1 -1] == 39)
		size1--;
	str = (char *)malloc(sizeof(char) * (size1 + ft_strlen(str2) + 1));
	if (!str)
		return (NULL);
	while (str1[++i] && i < size1)
		str[i] = str1[i];
	while (str2[++c])
		str[i + c] = str2[c];
	str[i + c] = '\0';
	return (str);
}

int	ft_var_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	while (str2[i] && str2[i] != '=')
		i++;
	if (ft_strlen(str1) != i)
		return (1);
	i = -1;
	while (str1[++i] && str2[i] != '=')
	{
		if (str1[i] != str2[i])
			return (1);
	}
	return (0);
}

char	*ft_add_var_value(char *str1)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (str1[i] && str1[i] != '=')
		i++;
	result = malloc(sizeof(char) * ft_strlen(str1) - i + 1);
	if (!result)
		ft_exit_error(NULL, "Malloc error", 17);
	while (str1[++j])
		result[j - 1] = str1[i + j];
	result[j] = '\0';
	return (result);
}

char	*ft_change_line_value(char *line, char *var)
{
	int		i;
	int		j;
	char	*final_line;

	j = 0;
	i = ft_search_next_char(line, '$', -1);
	while (line[i + j] && line[i + j] != ' ' && line[i + j] != 34 && line[i + j] != 39)
		j++;
	while (line[i + j])
		i++;
	final_line = malloc(sizeof(char) * i + ft_strlen(var));
	if (!final_line)
		ft_exit_error(NULL, "Malloc error", 18);
	final_line = ft_craft_result(final_line, line, var, j);
	free(line);
	free(var);
	return (final_line);
}

char	*ft_compare_var_name(t_cmd *cmd, char *line, char *name_var)
{
	int		i;
	char	*result;

	i = -1;
	while (++i < cmd->env->env_amount)
	{
		if (ft_var_strcmp(name_var, cmd->env->env[i]) == 0)
		{
			free(name_var);
			result = ft_add_var_value(cmd->env->env[i]);
			return (ft_change_line_value(line, result));
		}
	}
	return (NULL);
}
