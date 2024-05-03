/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_home_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:23:43 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/03 17:09:32 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_relative_home(char *command)
{
	int	i;

	i = -1;
	if (command && command[0] == '~' && (!command[1] || command[1] == '/'))
		return (1);
	return (0);
}

char	*ft_replace_home(char *str)
{
	char	*res;
	int		i;
	char	*temp;
	char	*temp2;

	i = 0;
	temp = ft_strdup(str + 1);
	res = ft_strdup(getenv("HOME"));
	if (!res)
		ft_exit_error("Malloc error", 50);
	temp2 = ft_strjoin(res, temp);
	free(res);
	free(temp);
	free(str);
	return (temp2);
}

char	*ft_replace_value_of_var_bis(char *str, int i, int j)
{
	char	*res;
	char	*tmp[3];

	tmp[0] = ft_itoa(g_exit_status);
	res = malloc(sizeof(char) * ((ft_strlen(str) - 1) + ft_strlen(tmp[0])));
	if (!res)
		exit_error("Error malloc", 55);
	tmp[1] = ft_substr(str, 0, i);
	tmp[2] = ft_strdup(tmp[1]);
	free(tmp[1]);
	tmp[1] = ft_strjoin("", tmp[0]);
	free(tmp[0]);
	tmp[0] = ft_strjoin(tmp[2], tmp[1]);
	j = -1;
	while (tmp[0][++j])
		res[j] = tmp[0][j];
	while (str[++i] && str[i + 1])
		res[j++] = str[i + 1];
	res[j] = '\0';
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(str);
	return (res);
}

char	*ft_replace_value_of_var(char *str)
{
	int i;
	int j;

	i = ft_locate_next_quote(0, str, '?') - 1;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
			str = ft_replace_value_of_var_bis(str, i, -1);
		j = i;
		i = ft_locate_next_quote(0, str, '$');
		if (j == i)
			break ;
	}
	return (str);
}
