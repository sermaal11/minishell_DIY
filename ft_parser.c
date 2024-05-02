/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:14:29 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/02 15:45:43 by smarin-a         ###   ########.fr       */
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
	*cmd = ft_add_command(mini, lines[0]);
	ft_expander(cmd);
	
}
