/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands-2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:35:49 by user              #+#    #+#             */
/*   Updated: 2024/06/27 12:57:11 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_position(char *input, int *size, int stop)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (stop-- != 0)
	{
		while (input[pos] == ' ')
			pos++;
		pos += size[i++];
	}
	while (input[pos] == ' ')
		pos++;
	return (pos);
}

char	*ft_inside_argv(char *input, int *size, int stop)
{
	char	*exit;
	int		i;
	int		pos;

	i = -1;
	exit = (char *)malloc((size[stop]) * sizeof(char *));
	if (exit == NULL)
		return (NULL);
	pos = ft_position(input, size, stop);
	while (++i < size[stop] - 1)
		exit[i] = input[pos++];
	exit[i] = '\0';
	printf(B_YE_0"EXIT --> [-%s-]\n", exit);
	return (exit);
}

int	ft_size_argv(char *input, int stop)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		if (input[i] != 34 && input[i] != 39 && input[i] != ' ')
			size++;
		if (input[i] == 34 || input[i] == 39)
			i = ft_process_quotes(input, &i, &size);
		if (input[i] == '\0' || (input[i + 1] == ' ' && --stop == -1))
			return (++size);
		else if (input[i] == ' ')
			size = 0;
		i++;
	}
	return (++size);
}

int	*ft_sizes_input(char *input, int argc)
{
	int	*sizes;
	int	i;

	i = -1;
	sizes = (int *)malloc(argc * sizeof(int *));
	if (sizes == NULL)
		return (0);
	while (++i < argc - 1)
		sizes[i] = ft_size_argv(input, i);
	return (sizes);
}

void	ft_free(char **argv, int *size, char ***args)
{
	int	i;
	
	i = 0;
	if (argv)
	{
		while (i < (int)ft_strlen(*argv))
			free(argv[i++]);
		free(argv);
	}
	if (size)
		free(size);
	*args = NULL;
}

void	ft_get_args(char *input, int argc, char ***args)
{
	char	**argv;
	int		*size;
	int		i;

	i = -1;
	argv = ft_calloc((argc + 2), sizeof(char *));
	if (argv == NULL)
        return (ft_free(NULL, NULL, args));
	size = ft_sizes_input(input, argc + 1);
	int j = -1;
	while (++j != argc)
		printf(B_CY_0"SIZE[%d] --> [-%d-]\n", j, size[j]);
	if (size == NULL)
		return (ft_free(argv, NULL, args));
	while (++i < argc)
	{
		argv[i] = ft_inside_argv(input, size, i);
		if (argv[i] == NULL)
			return (ft_free(argv, size, args));
	}
	argv[argc + 1] = NULL;
	free(size);
	*args = argv;
}
