/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 17:52:46 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/29 16:56:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_locate_final_red(int i, char *input)
{
	while (input[i]== '<' || input[i] == '>')
		i++;
	return (i);
}

void	ft_start_red(t_mini *mini)
{
	mini->flags->redirect = (t_red *)malloc(sizeof(t_red));
	if (mini->flags->redirect == NULL)
		return ;
	mini->flags->redirect->error = (char *)malloc(sizeof(char *) * 3);
	if (mini->flags->redirect->error == NULL)
		return ;
	mini->flags->redirect->red_error = 0;
	mini->flags->redirect->si_le = 0;
	mini->flags->redirect->si_ri = 0;
	mini->flags->redirect->do_le = 0;
	mini->flags->redirect->do_ri = 0;
}

void	ft_red(t_mini *mini, char *input)
{
	int	i;
	int	j;

	i = 0;
	while (input[i] != '\0')
	{
		j = i;
		i = ft_locate_final_red(i, input);
		if (i > j)
			mini->flags->red++;
		if (input[i] == '\0')
			i--;
		i++;
	}
}

void	ft_one(t_mini *mini, char *input)
{
	if (input[0] == '<')
		mini->flags->redirect->si_le += 1;
	if (input[0] == '>')
		mini->flags->redirect->si_ri += 1;
}

void	ft_two(t_mini *mini, char *input)
{
	if (input[0] == input[1])
	{
		if (input[0] == '<')
			mini->flags->redirect->do_le += 1;
		else
			mini->flags->redirect->do_ri += 1;
	}
	else
	{
		if (input[0] == '<')
			mini->flags->redirect->red_error = 1;
		mini->flags->redirect->error = ft_substr(input, 1, 1);
	}
}

void	ft_three(t_mini *mini, char *input)
{
	if (input[0] == input[1])
		mini->flags->redirect->error = ft_substr(input, 2, 1);
	else
		mini->flags->redirect->error = ft_substr(input, 1, 2);
	mini->flags->redirect->red_error = 1;
}

void	ft_four_plus(t_mini *mini, char *input)
{
	if (input[0] == input[1])
	{
		if (input[2] == input[3])
			mini->flags->redirect->error = ft_substr(input, 2, 2);
		else
			mini->flags->redirect->error = ft_substr(input, 2, 1);
	}
	else
		mini->flags->redirect->error = ft_substr(input, 1, 2);
	mini->flags->redirect->red_error = 1;
}

int	ft_count_redirect(t_mini *mini, char *input)
{
	int	*error;
	int	size;
	int	i;
	int	j;

	i = 0;
	j = 0;
	ft_start_red(mini);
	if (mini->flags->redirect->error == NULL || mini->flags->redirect == NULL)
		return (0);
	ft_red(mini, input);
	if (mini->flags->red == 0)
		return (0);
	error = (int *)malloc(sizeof(int *) * mini->flags->red);
	if (error == NULL)
		return (0);
	while (input[i] != '\0')
	{
		size = 0;
		mini->flags->redirect->red_error = 0;
		while ((input[i]== '<' || input[i] == '>') && i++ >= size)
			size++;
		if (size == 1)
			ft_one(mini, &input[i - size]);
		else if (size == 2)
			ft_two(mini, &input[i - size]);
		else if (size == 3)
			ft_three(mini, &input[i - size]);
		else if (size >= 4)
			ft_four_plus(mini, &input[i - size]);
		error[j++] = mini->flags->redirect->red_error;
		if (input[i] == '\0')
			break ;
		i++;
	}
	if (error)
		free(error);
	return (0);
}

// ERRORES

// Z = X && Z = Y
// W = !Z

// 1 = <>
// 2 = ><
// 3 = XX<
// 4 = XX>
// 5 = XYZ
// 6 = XXZZ
// 7 = XXZW
// 8 = XZZZ

int	ft_check_input(t_mini *mini, char *input, char ***lines)
{
	mini->flags->quote = ft_check_quote(input, 2, 2, mini);
	mini->flags->pipe = ft_count_pipes(input);
	mini->flags->red = ft_count_redirect(mini, input);
	if (mini->flags->quote == 0 && mini->flags->pipe == 0 && mini->flags->red == 0)
		return (1);
	if (mini->flags->pipe != 0)
	{
		// (*lines) = ft_split_pipes(input);
		if (lines == NULL)
			return (1);
	}
	// if (mini->flags->red != 0)								/* CREAR FUNCION ft_count_redirect y ft_split_redirects */
	// 	(*lines) = ft_split_redirects(mini, input);
	return (0);
}
