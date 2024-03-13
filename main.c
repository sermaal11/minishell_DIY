/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/13 18:13:12 by smarin-a         ###   ########.fr       */
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
	
	printf("%s\n", env[1]);
	atexit(leaks);
	return (0);
}
