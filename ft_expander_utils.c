/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 18:04:30 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/03 12:48:05 by smarin-a         ###   ########.fr       */
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
	while (str1[i] && i < size1)
	{
		str[i] = str1[i];
		i++;
	}
	while (str2[c])
	{
		str[i + c] = str2[c];
		c++;
	}
	str[i + c] = '\0';
	return (str);
}
