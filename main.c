/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sergio <sergio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 12:09:37 by smarin-a          #+#    #+#             */
/*   Updated: 2024/04/30 12:18:50 by sergio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks -q minishell");
}

int g_exit_status;

int	main(int argc, char **argv, char **env)
{
	t_mini	*mini;

	if (argc != 1)
		ft_many_args_error(argv);
	mini = ft_initialize(env);
	g_exit_status = 0;
	ft_mini_header();
	//ft_signal_management(1);
	
	// todo: 1. Lectura de comandos: La shell lee los comandos ingresados por el
	// todo: usuario desde la línea de comandos. (ft_lexer.c)
	ft_recive_input(mini);
	
	atexit(leaks);
	return (0);
}
