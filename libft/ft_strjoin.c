/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:01:27 by sergio            #+#    #+#             */
/*   Updated: 2024/05/29 10:53:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		size_total;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	size_total = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	ptr = (char *)ft_calloc(sizeof(char), size_total + 1);
	if (ptr == NULL)
		return (NULL);
	while ((char *)s1 && (char)s1[i] != '\0')
		ptr[j++] = (char)s1[i++];
	j = 0;
	while ((char *)s2 && (char)s2[j] != '\0')
		ptr[i++] = (char)s2[j++];
	ptr[i] = '\0';
	if (s1)
		free((char *)s1);
	return (ptr);
}
