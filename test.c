/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:10:47 by user              #+#    #+#             */
/*   Updated: 2024/05/31 15:57:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_dolar(char *str, int i, int j)
{
	while (str[i] != '\0')
	{
		if (str[i++] == '$')
			j++;
	}
	return (j);
}

int	*ft_size_total(char **env, char *str)
{
	int	*sizes;
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	sizes = (int *)malloc(sizeof(int *) * ft_count_dolar(str, 0, 0) + 1);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && str[i] != '$')
			printf("%c\n", str[i++]);
		if (str[i] == '\0' || str[i + 1] == '\0' || ft_isdigit(str[i + 1]) == 1)
		{	
			free(sizes);
			return (0);
		}
		if (str[i++] == '$')
		{
			while (ft_isalnum(str[i++]) == 1)
			{
				printf("%c\n", str[i]);
				j++;
			}
		}
		sizes[l++] = j;
		i++;
	}
	sizes[l] = -1;
	return (sizes);
}

char	*ft_expand(char **env, char *str) // Pasar cadena ya limpia y partida por redirecciones y pipes;
{
	int	i;
	int	*sizes;
	
	i = 0;
	// while (env[i] != NULL)
	// 	// printf("\n    ---------------------------------------------------\n\n"OR1"\t%s\n"RESET, env[i++]);
	// 	i++;
	printf(CYAN"\n\t%s\n"RESET, str);
	sizes = ft_size_total(env, str);
	if (sizes[0] == 0)
		return (NULL);
	while (sizes[i] != -1)
		printf(CYAN"%d\n"RESET, sizes[i++]);
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	char	*str = "ls -a $asd $ddd";
	char	*final;

	if (argc != 1)
		return (printf(BOLD_RED"ERROR --> %s\n"RESET, argv[1]), 0);
	final = ft_expand(env, str);
	printf(GREEN"\n\t%s\n"RESET, final);

	return (0);
}