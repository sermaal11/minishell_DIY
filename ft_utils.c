/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:24:41 by smarin-a          #+#    #+#             */
/*   Updated: 2024/03/15 17:33:17 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	printf("                              By Descamil & Smarin-a\n");
	printf("\n\n\n");
}
