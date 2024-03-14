/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/14 18:14:27 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

int main(int argc, char **argv, char **env)
{
	// ! t_mini	mini;
	
	// ? Control de argumentos (DONE)
	if (argc != 1)
		ft_many_args_error(argv);
	
	// ? Establece variable global "exit_status = 0" (DONE)
	g_exit_status = 0;
	
	// ? Printeo de cabecera (DONE)
	ft_mini_header();
	
	// ! Inicializador de variables y estructuras para evitar errores (ft_utils.c)
	// ! mini = ft_initialize( * no se lo que va a qui de momento * );
	
	
	// ? Gestion de señales de la terminal (DONE)
	ft_signal_management(1);
	// 1. Lectura de comandos: La shell lee los comandos ingresados por el 
	// ususario desde la línea de comandos. (ft_lexer.c)
	ft_recive_input();	// ! (&mini)
	
	printf(PURPLE"%s\n"RESET, env[1]);
	atexit(leaks);
	return (0);
}
