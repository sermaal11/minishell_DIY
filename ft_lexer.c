/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/04/30 12:36:51 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_recive_input(t_mini *mini)
{
	char *input;
	
	while(1)
	{
		// ? Entrada de input desde readline (DONE)
		input = readline("🐚"GREEN" MiniShell"RESET" --> ");
		// ? Control en caso de input == NULL (Gestion de señales) (DONE)
		if (!input)
			ft_exit_error("Exit", g_exit_status);
		// * ft_parser.c
		// ? Parseo para input == " " || input[0] == '\0' (DONE)
		if (ft_check_void_input(input) == -1 || input[0] == '\0')
			printf("");	
		else
		{
			add_history(input);

			// ! Nucleo del parseo
		}
		
		// todo: Proto built-ins: exit (Irá en ft_built_ins.c y sera llamada 
		// todo: desde el ejecutor).
		// ! Si te pasan un (int)num despues, exit_status = (int)num
		// * Ejemplo: exit 43
		// * echo $? = 43
		
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