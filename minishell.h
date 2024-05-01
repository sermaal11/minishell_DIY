/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/01 13:30:15 by smarin-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Colors
// Regular
# define RESET "\033[0m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define OR1 "\033[38;5;208m" // Naranja claro
# define OR2 "\033[38;5;214m" // Naranja medio
# define OR3 "\033[38;5;220m" // Naranja oscuro
# define YE1 "\033[38;5;226m" // Amarillo claro
# define YE2 "\033[38;5;229m" // Amarillo medio
# define YE3 "\033[38;5;227m" // Amarillo oscuro
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

// Bold
# define BOLD_RED "\033[1;31m"
# define BOLD_GREEN "\033[1;32m"
# define BOLD_YELLOW "\033[1;33m"
# define BOLD_BLUE "\033[1;34m"
# define BOLD_PURPLE "\033[1;35m"
# define BOLD_CYAN "\033[1;36m"
# define BOLD_WHITE "\033[1;37m"

// Librerias
# include "./libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <signal.h>
# include <limits.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include <readline/readline.h>
# include <readline/history.h>

# define R 0
# define W 1

extern int g_exit_status;

typedef struct s_token
{
	char	*input;
	char	**tokens;
}				t_token;

typedef struct s_flags
{
	
}				t_flags;

typedef struct s_env
{
	int		env_amount;
	char	*path;
	char	**env;
}				t_env;

typedef struct s_mini
{
	int		shell_level;

	t_env	*env;
	t_flags	*flags;
	t_token	*token;
}				t_mini;

//ft_utils.c
void	ft_mini_header(void);

//ft_initialize.c
t_mini	*ft_initialize(char **env);

//ft_signals.c
void	ft_signal_management(int n);

//ft_lexer.c
void	ft_recive_input(t_mini *mini);

//ft_parser.c

// ft_error_management.c
void	ft_many_args_error(char **argv);
void	ft_put_error(char *bash, char *file, char *error_msg);
void	ft_exit_error(char *error_msg, int exit_status);

#endif