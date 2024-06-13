/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:37:17 by descamil          #+#    #+#             */
/*   Updated: 2024/06/13 11:27:29 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size(char **names)
{
	int	size = 0;
	int	i = 0;

	while (names[i])
	{
		printf("%s\n", names[i]);
		size += ft_strlen(names[i++]);
	}
	return (size);
}

char	*ft_remove_wrong_var(char *str, int *wrong_value)
{
	int		var = 0;
	int		*pos = malloc(sizeof(int *) * ft_var(str));
	char	**names;
	char	*final;
		
	names = ft_names_var(str, &var, &pos);
	int	i = 0;
	while (names[i])
		free(names[i++]);
	free(names);
	
	// printf("%d\n", var);
	// printf("%d\n", ft_size(names));
	int	size = 0;
	i = 0;
	if (wrong_value)
	{
		while (i  != ft_size_int(wrong_value))
		{
			printf("%d\n", i);
			size += wrong_value[i++];
		}
	}

	final = malloc(sizeof(char) * (ft_strlen(str) - size + 1));
	i = 0;
	int	final_i = 0;
	int	aux = 0;

	while (str[i] != '\0' && (unsigned long)i < ft_strlen(str) - size)
	{
		while (str[i] != '\0' && i != ft_size_int(pos) && i != pos[aux])
		{
			// printf("[%d] --> %c\n", i, str[i]);
			final[final_i++] = str[i++];
		}
		int l = 0;
		while (l++ != wrong_value[aux])
			i++;
		aux++;
	}
	final[final_i] = '\0';
	free(pos);
	printf("%s\n", final);
	free(wrong_value);
	return (final);
}


// int	main()
// {
// 	char	*str = "ls $USRen_GB.UTF-8 $U $AGE en_GB.UTF-8";
// 	char	*final;
// 	int		*wrong_value;

// 	wrong_value = malloc(sizeof(int *) * 3);
// 	wrong_value[0] = 4;
// 	wrong_value[1] = 2;
// 	wrong_value[2] = 4;

	
// 	final = ft_remove_wrong_var(str, wrong_value);
// 	free(final);
// 	return (0);
// }