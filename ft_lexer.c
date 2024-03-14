/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/14 18:14:39 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_recive_input(void) //(t_mini *mini)
{
	char *input;
	
	while(1)
	{
		input = readline("🐚"GREEN" MiniShell"RESET" --> ");
		printf(YELLOW"input --> %s\n"RESET, input);
		if (!input)
			ft_exit_error("Exit", g_exit_status);
		
		// ! ft_parser.c
		if (ft_check_void_input(input) == -1 || input[0] == '\0')
			printf("");	
		else
		{
			add_history(input);
		}
		
		// ! Proto built-ins: exit (Irá en ft_built_ins.c y sera llamada desde 
		// ! el ejecutor) Si te pasan un (int)num despues exit_status = (int)num
		if (ft_strncmp(input, "exit", ft_strlen("exit")) == 0)
		{
			g_exit_status = 0;
			free(input);
			break ;
			// ft_exit_error("Exit", exit_status);
		}
		
		if (input != NULL)
			free(input);
	}
}