/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 16:10:47 by user              #+#    #+#             */
/*   Updated: 2024/05/14 10:40:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_comillas(char *exit, char *input, int *ref, int size, int index)
{
	int j;
	int	i;

	i = ref[0];
	printf("I == %d\n", i);
	j = i;
	printf("INPUT[i] - 1 = %c --> I = %d\n", input[i], i);
	while (input[i] == 34 || input[i] == 39)
		i = ft_locate_next_quote(i + 1, input, input[i]);
	printf("INPUT[i] - 2 = %c --> I = %d\n", input[i], i);
	while (j < i && input[j] != '\0')
	{
		exit[index++] = input[j];
		printf("INPUT = %c --- J = %d\n", input[j++], j);
	}
	printf("INPUT[i] - 3 = %c\n", input[i]);
	if (exit[j] == '\0')
		return (exit);
	printf("INPUT[i] - 4 = %c\n", input[i]);
	if (input[i] != 34 && input[i] != 39 && input[i] != '\0')
	{
		index = 0;
		ft_bzero(exit, size);
	}
	printf("INPUT[i] - 5 = %c\n\n----------------\n\n", input[i]);
	if (input[i] == ' ')
		return (exit);
	return (exit);
}

char	*ft_spacend(char *exit, int index, int stop, int size)
{
	if (exit != NULL && stop == 0)
		exit[index] = '\0';
	else
		ft_bzero(exit, size + 1);
	return (exit);
}

char	*ft_inside_argv(char *input, int size, int stop)
{
	int		i;
	int		index;
	char	*exit;

	i = -1;
	index = 0;
	exit = NULL;
	exit = (char *)malloc((size + 1) * sizeof(char *));
	if (exit == NULL)
		return (NULL);
	while (input[++i] != '\0')
	{
		if (input[i] != 34 && input[i] != 39 && input[i] != ' ' && stop == 0)
		{
			// printf("CHAR = %c -- INDEX = %d\n",input[i], index);
			exit[index++] = input[i];
		}
		printf("555 --> %s\n", exit);
		if (input[i] == 34 || input[i] == 39)
		{
			printf("EXIT --> %s\n", exit);
			exit = ft_comillas(exit, input, &i, size, index - 1);
		}
		if (input[i] == ' ')
		{
			exit = ft_spacend(exit, index, stop, size);
			// printf("CHAR = %c -- INDEX = %d -- STOP = %d -- EXIT = %s\n",input[i], index, stop , exit);
			if (exit[index] == '\0' && stop == 0)
			{
				printf("\n--------------\nSALIDA = 1\nExit = %s\n--------------\n\n", exit);
				return (exit);
			}
			else
			{
				stop--;
				index = 0;
			}
		}
	}
	// printf("CHAR = %c -- INDEX = %d -- STOP = %d -- EXIT = %s\n",input[i], index, stop , exit);
	printf("\n--------------\nSALIDA = 2\nExit = %s\n--------------\n\n", exit);
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
		if (input[i] == ' ')
		{
			if (first != 0 && stop-- == 0)
				return (first + 1);
			first = 0;
		}
		if (input[i] == 34 || input[i] == 39)
		{
			j = i;
			i = ft_locate_next_quote(i + 1, input, input[i]);
			while (j++ <= i)
				first++;
		}
	}
	if (first != 0 && stop == 0)
		return (first + 1);
	return (0);
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
	}
	i = -1;
	while (++i < argc)
		argv[i] = ft_inside_argv(input, size[i], i);
	argv[i] = NULL;
	return (argv);
}

void	leaks(void)
{
	system("leaks -q minishell");
}

int main()
{
	char	**argv;
	int		size = 0;
	char 	*ptr = "a \"A\"";
	int		i = 0;
	
	argv = ft_get_args(ptr, 2);
	while (argv[i] != NULL)
		printf("%s\n", argv[i++]);
	// printf("%d\n", ft_size_argv(ptr, 0));
	
	atexit(leaks);
	return (0);
}

