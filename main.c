/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/13 19:09:00 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

void	ft_mini_header(void)
{
	printf("\n\n");
	printf(BOLD_CYAN" /$$      /$$ /$$$$$$ /$$   /$$ /$$$$$$  /$$$");
	printf("$$$  /$$   /$$ /$$$$$$$$ /$$       /$$      \n");
	printf("| $$$    /$$$|_  $$_/| $$$ | $$|_  $$_/ /$$__");
	printf("  $$| $$  | $$| $$_____/| $$      | $$      \n");
	printf("| $$$$  /$$$$  | $$  | $$$$| $$  | $$  | $$  ");
	printf("\\__/| $$  | $$| $$      | $$      | $$      \n");
	printf("| $$ $$/$$ $$  | $$  | $$ $$ $$  | $$  |  $$$");
	printf("$$$ | $$$$$$$$| $$$$$   | $$      | $$      \n");
	printf("| $$  $$$| $$  | $$  | $$  $$$$  | $$   \\___");
	printf("_  $$| $$__  $$| $$__/   | $$      | $$      \n");
	printf("| $$\\  $ | $$  | $$  | $$\\  $$$  | $$   /$$");
	printf("  \\ $$| $$  | $$| $$      | $$      | $$      \n");
	printf("| $$ \\/  | $$ /$$$$$$| $$ \\  $$ /$$$$$$|  $$");
	printf("$$$$/| $$  | $$| $$$$$$$$| $$$$$$$$| $$$$$$$$\n");
	printf("|__/     |__/|______/|__/  \\__/|______/ \\___");
	printf("___/ |__/  |__/|________/|________/|________/\n\n\n"RESET);
	printf("                                By Descamil & Smarin-a\n");
	printf("\n\n\n");
}

int main(int argc, char **argv, char **env)
{
	if (argc != 1)
		ft_many_args_error(argv);
		
	// Printeo de cabecera
	ft_mini_header();
	
	//Gestion de señales de la terminal
	// ! Revisar el wait signal de GITHUB de gemartin:
	ft_wait_signal(1);
	
	// 1. Lectura de comandos: La shell lee los comandos ingresados por el usuario 
	// desde la línea de comandos o desde un script.
	char *input_line;
	
	while(1)
	{
		input_line = readline("🐚"GREEN" MiniShell"RESET" --> ");
		add_history(input_line);
		free(input_line);
	}
	
	printf(PURPLE"%s\n"RESET, env[1]);
	atexit(leaks);
	return (0);
}
