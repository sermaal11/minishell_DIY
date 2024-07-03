/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_red_old.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 17:10:54 by descamil          #+#    #+#             */
/*   Updated: 2024/07/02 10:09:53 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection(char c, char c1)
{
	if (c == '<' || c == '>')
	{
		if (c1 == '<' || c1 == '>')
			return (2);
		return (1);
	}
	return (0);
}

void	add_token(char **tokens, int *token_count, char *token)
{
	tokens[*token_count] = ft_strdup(token);
	(*token_count)++;
}

char	*extract_token(char *input, int *i)
{
	char	*token;
	int		token_start;
	int		token_len;
	int		len;

	len = ft_strlen(input);
	while (*i < len && input[*i] == ' ')
		(*i)++;
	token_start = *i;
	while (*i < len && !ft_isspace(input[*i])
		&& is_redirection(input[*i], input[*i + 1]) == 0)
		(*i)++;
	token_len = *i - token_start + 1;
	token = (char *)malloc((token_len + 1) * sizeof(char));
	ft_strlcpy(token, input + token_start, token_len);
	return (token);
}

void	skip_redirection(char *input, int *i)
{
	int	len;

	len = ft_strlen(input);
	if (*i < len)
		*i += is_redirection(input[*i], input[*i + 1]);
}

char	**custom_split(char *input)
{
	char	**tokens;
	char	*token;
	int		token_count;
	int		len;
	int		i;

	i = 0;
	token_count = 0;
	len = ft_strlen(input);
	tokens = (char **)malloc(sizeof(char *) * (len * 2 + 1));
	if (!tokens)
	{
		perror("Malloc error\n");
		exit(1);
	}
	while (i < len)
	{
		token = extract_token(input, &i);
		if (ft_strlen(token) > 0)
			add_token(tokens, &token_count, token);
		free(token);
		skip_redirection(input, &i);
	}
	tokens[token_count] = NULL;
	return (tokens);
}

int	ft_count_fds(char *input)
{
	int	count;
	int i;
	int	r;

	count = 0;
	i = 0;
	while (input[i] != '\0')
	{
		r = is_redirection(input[i], input[i + 1]);
		if (r != 0)
		{
			i += r;
			if (input[i - 1] == '>' || input[i - 1] == '<')
				count++;
		}
		i++;
	}
	return (count);
}

int	*ft_fd_value(char *input)
{
	int	*fds;

	fds = (int *)ft_calloc(sizeof(int), ft_count_fds(input));
	return (fds);
}

int	main()
{
	char *input = "<a<a<a<a<a<a<a<a<a<a<a<a<a<a<a";
	t_argv *tokens;
	int i = 0;

	tokens = ft_calloc(sizeof(t_argv), 1);
	tokens->argv = custom_split(input);
	if (tokens->argv)
	{
		while (tokens->argv[i] != NULL) 
		{
			printf("SPLIT[%d] --> %s\n", i, tokens->argv[i]);
			free(tokens->argv[i++]);
		}
		free(tokens->argv);
	}
	printf("%d\n", ft_count_fds(input));
	// tokens->fds = ft_fd_values(input);
	free(tokens);
	return 0;
}
