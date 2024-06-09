/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commands-2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:35:49 by user              #+#    #+#             */
/*   Updated: 2024/06/07 12:58:40 by descamil         ###   ########.fr       */
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
	exit = (char *)malloc((size[stop] + 1) * sizeof(char *));
	if (exit == NULL)
		return (NULL);
	pos = ft_position(input, size, stop);
	while (++i < size[stop] - 1)
		exit[i] = input[pos++];
	exit[i] = '\0';
	return (exit);
}

int	ft_size_argv(char *input, int stop)
{
	int	i;
	int	first;

	i = 0;
	first = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		if (input[i] != 34 && input[i] != 39 && input[i] != ' ')
			first++;
		if (input[i] == 34 || input[i] == 39)
		{
			i = ft_process_quotes(input, &i, &first);
			if (input[i] == '\0' || (input[i] == ' ' && stop == 0))
				return (++first);
		}
		if (input[i] == '\0' || (input[i] == ' ' && stop == 0))
			return (++first);
		else if (input[i])
			ft_process_space(input, &i, &first, &stop);
		i++;
	}
	return (++first);
}

int	*ft_sizes_input(char *input, int argc)
{
	int	*sizes;
	int	i;

	i = -1;
	sizes = (int *)malloc(argc * sizeof(int *));
	if (sizes == NULL)
		return (0);
	while (++i < argc)
		sizes[i] = ft_size_argv(input, i);
	return (sizes);
}

void	ft_get_args(char *input, int argc, char ***args)
{
	char	**argv;
	char	*arg;
	int		*size;
	int		i;

	i = -1;
	argv = ft_calloc((argc + 2), sizeof(char *));
	if (argv == NULL)
    {
        *args = NULL;
        return ;
    }
	size = ft_sizes_input(input, argc + 1);
	if (size == NULL)
	{
		free(argv);
		*args = NULL;
		return ;
	}
	while (++i < argc)
	{
		argv[i] = (char *)malloc(size[i] * sizeof(char));
		if (argv[i] == NULL)
		{
			while (--i >= 0)
				free(argv[i]);
			free(argv);
			free(size);
			*args = NULL;
			return ;
		}
		arg = ft_inside_argv(input, size, i);
		if (arg == NULL)
		{
			while (--i >= 0)
				free(argv[i]);
			free(argv);
			free(size);
			*args = NULL;
			return ;
		}
		if (argv && argv[i])
			ft_strlcpy(argv[i], arg, 5);
		free(arg);
	}
	argv[argc + 1] = NULL;
	free(size);
	*args = argv;
}
