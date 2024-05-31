/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/31 10:51:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_void_input(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] != '\0')
		j += ft_isspace(input[i++]);
	if (j == i)
		return (-1);
	return (0);
}

void	ft_recive_input(t_mini *mini)
{
	char *input;
	
	(void) mini;
	while (1)
	{
		input = readline("🐚"GREEN" MINI(S)HELL"RESET" 🔥 -> ");
		if (!input)
		{
			free(input);
			input = NULL;
			ft_exit_error("Exit", g_exit_status);
		}
		if (ft_check_void_input(input) == -1 || input[0] == '\0')
			(void)input;
		else
		{
			add_history(input);
			// TODO: HECHO HASTA AQUI y funcional COn señales incluidas
			// ? HASTA AQUI FUNCIONA TODO (CREO)
			// ! Nucleo del parseo
			// El parseo no funciona
			// este proyecto es una mierda
			// No se que mas hacer
			// ! AYUDA:
			if (ft_strtok(mini, &(mini->cmd), input) && mini->flags->quote != 0)
			{
				printf("Llega al final! 🚀\n");
						}
			if (mini->flags->redirect->red_error != 0)
				printf("mini: parse error near `%s'\n", mini->flags->redirect->error);
		}
		// todo: Proto built-ins: exit (Irá en ft_builtins.c y sera llamada desde el ejecutor)
		if (ft_strncmp(input, "exit", ft_strlen("exit")) == 0)
		{
			//g_exit_status = 0;
			//ft_exit_error("Exit", g_exit_status);
			// ! Las dos lineas de arriba son las que valen, estas son para debuguear.
			free(input);
			input = NULL;
			break ;
		}
		if (input != NULL)
		{
			free(input);
			input = NULL;
		}
	}
}
