/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_final_values.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 17:24:29 by descamil          #+#    #+#             */
/*   Updated: 2024/07/08 10:55:22 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_dup(char	*argv)
{
	int	i;
	int	space;
	
	i = 0;
	space = 0;
	if (argv)
	{
		while (argv[i] != '\0')
		{
			if (argv[i++] == ' ')
				space++;
		}
	}
	return (i - space);
}

int	ft_dups(char *argv)
{
	if (argv == NULL)
		return (0);
	if (ft_strnstr(argv, "<", 1) && (int)ft_strlen_dup(argv) == 1)
		return (1);
	if (ft_strnstr(argv, ">", 1) && (int)ft_strlen_dup(argv) == 1)
		return (1);
	if (ft_strnstr(argv, "<<", 2) && (int)ft_strlen_dup(argv) == 2)
		return (1);
	if (ft_strnstr(argv, ">>", 2) && (int)ft_strlen_dup(argv) == 2)
		return (1);
	return (0);
}	

int	ft_check_dups(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i + 1])
	{
		if (ft_dups(cmd->args[i]) == 1 && ft_dups(cmd->args[i + 1]) == 1)
		{
			printf("mini: syntax error near unexpected token `%s'\n", cmd->args[i + 1]);
			return (-1);
		}
		i++;
	}
	return (0);
}

char	**ft_order(t_cmd *cmd, t_mini *mini)
{
	// int i;

	// i = 0;
	if (ft_check_dups(cmd) == -1)
		return (NULL);
	while (cmd->args)
	{
		mini->flags->redirect->number += 0;
	}
	return (NULL);
}

void	ft_files(t_cmd *cmd, t_mini *mini, t_files *files)
{
	mini->flags->pipe += 1 - 1;
	files->order = ft_order(cmd, mini);
	if (files->order == NULL)
	{
		files->error = -1;
		return ;
	}
	// while (cmd->args)
	// {
		
	// }
}