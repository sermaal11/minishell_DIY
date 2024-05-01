/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/01 13:30:20 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_void_input(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
		j = j + ft_isspace(input[i++]);
	if (j == i)
		return (-1);
	return (0);
}

void ft_recive_input(t_mini *mini)
{
	char *input;
	
	(void) mini;
	while(1)
	{
		//Entrada de input desde readline (DONE)
		input = readline("🐚"GREEN" MiniShell"RESET" --> ");
		//Control en caso de input == NULL (Gestion de señales) (DONE)
		if (!input)
			ft_exit_error("Exit", g_exit_status);
		// * ft_parser.c
		//Parseo para input == " " || input[0] == '\0' (DONE)
		if (ft_check_void_input(input) == -1 || input[0] == '\0')
			(void)input;
		else
		{
			add_history(input);
			// ! Nucleo del parseo
			
		}
		
		// todo: Proto built-ins: exit (Irá en ft_builtins.c y sera llamada desde el ejecutor)
		if (ft_strncmp(input, "exit", ft_strlen("exit")) == 0)
		{
			//g_exit_status = 0;
			//ft_exit_error("Exit", g_exit_status);
			// ! Las dos lineas de arriba son las que valen, estas son para debuguear.
			free(input);
			break ;
		}
		
		if (input != NULL)
			free(input);
	}
}