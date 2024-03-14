/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/14 14:27:06 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

int main(int argc, char **argv, char **env)
{
	//Control de argumentos
	if (argc != 1)
		ft_many_args_error(argv);
	
	//Establecer variable global "exit_status = 0"
	exit_status = 0;
		
	// Printeo de cabecera
	ft_mini_header();
	
	// ! Inicializador de variables y estructuras para evitar errores
	
	
	// ! Gestion de señales de la terminal
	// ft_signal_management(1);
	
	
	// 1. Lectura de comandos: La shell lee los comandos ingresados por el usuario 
	// desde la línea de comandos.
	char *input_line;
	
	while(1)
	{
		input_line = readline("🐚"GREEN" MiniShell"RESET" --> ");
		add_history(input_line);
		// if (ft_strncmp(input_line, "exit", ft_strlen("exit")) == 0)
		// {
		// 	printf("exit\n");
		// 	free(input_line);
		// }
		// free(input_line);
	}
	
	printf(PURPLE"%s\n"RESET, env[1]);
	atexit(leaks);
	return (0);
}
