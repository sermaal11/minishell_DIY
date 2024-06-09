/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/06/09 10:51:54 by descamil         ###   ########.fr       */
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

char	*ft_free_input(t_mini *mini, char *input)
{
	int	j;

	j = 0;
	while (input && input[j] == ' ')
		j++;
	if (input[j] != '\0')
	{
		if (mini->cmd)
		{
			if (mini->cmd->cmd)
				free(mini->cmd->cmd);
			if (mini->cmd->args)
			{
				j = 0;
				while (mini->cmd->args[j] && mini->cmd->args[j] != NULL)
					free(mini->cmd->args[j++]);
				free(mini->cmd->args);
			}
			free(mini->cmd);
		}
	}
	free(input);
	return (NULL);
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
			ft_exit_error(mini, "Exit", g_exit_status);
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
			input = ft_free_input(mini, input);
	}
}
