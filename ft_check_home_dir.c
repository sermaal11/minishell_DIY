/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_home_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:23:43 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/03 13:05:04 by smarin-a         ###   ########.fr       */
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
