/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:14:29 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/02 13:35:55 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	int		i;
	char	**lines;
	t_cmd	*tmp;

	i = 0;
	lines = NULL;
	mini->char_amount = 0;
	if(ft_check_input(&mini, input, &lines))
		return (0);
	*cmd = 
}
