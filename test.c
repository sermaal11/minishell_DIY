/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:10:47 by user              #+#    #+#             */
/*   Updated: 2024/05/21 10:39:46 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_inside_argv(char *input, int *size, int stop)
{
	char	*exit;
	int		i;
	int		pos;
	int		actual;

	actual = 0;
	pos = 0;
	exit = (char *)malloc((size[stop] + 1) * sizeof(char *));
	if (exit == NULL)
		return (NULL);
	while (stop-- != 0)
	{
		pos += size[actual++];
		while (input[pos] == ' ')
			pos++;
	}
	i = -1;
	while (++i < size[actual])
		exit[i] = input[pos + i];
	exit[i] = '\0';
	return (exit);
}

int	ft_size_argv(char *input, int stop)
{
	int	i;
	int	j;
	int	first;

	i = -1;
	first = 0;
	while (input[++i])
	{
		if (input[i] != 34 && input[i] != 39 && input[i] != ' ')
			first++;
		if (input[i] == 34 || input[i] == 39)
		{
			j = i;
			while (input[i] == 34 || input[i] == 39)
				i = ft_locate_next_quote(i + 1, input, input[i]) + 1;
			while (j++ < i)
				first++;
			if (input[i] == '\0' || (input[i] == ' ' && stop-- == 0))
				return (first);
			else
				first = 0;
		}
	}
	return (first);
}

int *ft_sizes_input(char *input, int argc)
{
	int *sizes;
	int i;

	i = -1;
	sizes = (int *)malloc(argc * sizeof(int *));
	if (sizes == NULL)
		return (0);
	while (++i < argc)
		sizes[i] = ft_size_argv(input, i);
	return (sizes);
}

char **ft_get_args(char *input, int argc)
{
	char	**argv;
	int		*size;
	int		i;

	i = -1;
	argv = (char **)malloc((argc + 1) * sizeof(char *));
	if (argv == NULL)
		return (NULL);
	argv[argc] = NULL;
	size = ft_sizes_input(input, argc);
	while (++i < argc)
	{
		argv[i] = (char *)malloc(size[i] * sizeof(char *));
		if (argv[i] == NULL)
		{
			while (--i >= 0)
				free(argv[i]);
			free(argv);
			free(size);
			return (NULL);
		}
		argv[i] = ft_inside_argv(input, size, i);
	}
	argv[i] = NULL;
	return (argv);
}