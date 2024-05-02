/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_home_dir.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:23:43 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/02 17:30:08 by smarin-a         ###   ########.fr       */
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
