/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:49 by descamil          #+#    #+#             */
/*   Updated: 2024/06/13 15:30:29 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strnstr_mini(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	if (*s2 == '\0')
		return (0);
	while (s1[i] != '\0' && i < len)
	{
		if (s1[i] == s2[j])
		{
			k = i;
			while (s1[k] == s2[j] && s2[j] != '\0' && (k < len))
			{
				k++;
				j++;
				if (s2[j] == '\0')
					return (1);
			}
			j = 0;
		}
		i++;
	}
	return (0);
}

int	ft_final_var(int *k, char *input, int i)
{
	(*k)++;
	while (input[i] != '\0' && input[i] != ' ')
	{
		i++;
		(*k)++;
		if (input[i] == '$')
			return (i);
		
	}
	return (i);
}


int	ft_var(char *input)
{
	int		i;
	int		j;
	
	i = 0;
	j = 0;
	while (input[i] != '\0')
	{
		if (input[i++] == '$')
		{
			j++;
			if (input[i] == '$')
			{
				j--;
				i++;
			}
		}
	}
	return (j);
}

char	*ft_remove_var(char *dst, const char *src, int num, int i)
{
	while (src[num] != '\0')
		dst[i++] = src[num++];
	while (dst[i] != '\0')
		dst[i++] = '\0';
	return (dst);
}

int	ft_var_mod(char **env, char **names)
{
	int 	i;
	int		j;
	int		size;
	
	i = 0;
	size = 0;
	while (names && names[i] != NULL)
	{
		j = 0;
		while (env[j] != NULL)
		{
			if (ft_strnstr_mini(env[j], names[i], ft_strlen(names[i])) == 1)
				size++;
			j++;
		}
		i++;
	}
	return (size);
}

int	ft_size(char **names)
{
	int	size = 0;
	int	i = 0;

	while (names[i])
		size += ft_strlen(names[i++]);
	return (size);
}

char	*ft_remove_wrong_var(char *str, int *wrong_value)
{
	int		var = 0;
	int		*pos = malloc(sizeof(int *) * (ft_var(str) + 1));
	char	**names;
	char	*final;
		
	names = ft_names_var(str, &var, &pos);
	int	i = 0;
	while (names[i])
		free(names[i++]);
	free(names);
	int	size = 0;
	i = 0;
	if (wrong_value)
	{
		while (i  != ft_size_int(wrong_value))
			size += wrong_value[i++];
	}

	final = malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	i = 0;
	int	final_i = 0;
	int	aux = 0;

	while (str[i] != '\0' && (unsigned long)i < ft_strlen(str) - size)
	{
		while (str[i] != '\0' && i != ft_size_int(pos) && i != pos[aux])
			final[final_i++] = str[i++];
		int l = 0;
		while (l < ft_size_int(wrong_value) && l++ != wrong_value[aux])
			i++;
		aux++;
	}
	final[final_i] = '\0';
	free(pos);
	free(wrong_value);
	return (final);
}
