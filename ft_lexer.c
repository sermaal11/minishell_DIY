/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:50:54 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/07 12:23:28 by user             ###   ########.fr       */
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
	char	*input;
	int		i;

	(void) mini;
	while(1)
	{
		input = readline("🐚"GREEN" MINI(S)HELL"RESET" 🔥 -> ");
		if (!input)
			ft_exit_error("Exit", g_exit_status);
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
			i = 42;
			printf("%s\n", input);
			printf("%d\n", i);
			// while (mini->cmd->args[++i] != NULL)
			// 	printf("mini -> cmd -> args[%d] %s\n", i, mini->cmd->args[i]);

			// printf("mini -> cmd -> args_amount %d\n", mini->cmd->args_amount);
			
			// printf("mini -> cmd -> cmd %s\n", mini->cmd->cmd);

			// printf("mini ->cmd -> flags -> dollar %d\n", mini->cmd->flags->dollar);

			// printf("mini ->cmd -> flags -> pipe %d\n", mini->cmd->flags->pipe);

			// printf("mini ->cmd -> flags -> quote %d\n", mini->cmd->flags->quote);
			
			//if (ft_strtok(mini, &mini->cmd, input) && mini->flags->quote != 0)
			//{
				//printf("Llega al final! 🚀\n");
			//}
			
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