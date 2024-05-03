/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smarin-a <smarin-a@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 13:18:57 by smarin-a          #+#    #+#             */
/*   Updated: 2024/05/03 17:51:41 by smarin-a         ###   ########.fr       */
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
	int		quote;
	int		pipe;
	int		dollar;
}				t_flags;

typedef struct s_env
{
	int		env_amount;
	char	*path;
	char	**env;
}				t_env;

typedef struct s_cmd
{
	struct s_cmd	*next;
	t_env			*env;
	t_flags			*flags;
	char			*cmd;
	char			**args;
	int				args_amount;
}				t_cmd;

typedef struct s_mini
{
	int		shell_level;
	int 	char_amount;
	t_env	*env;
	t_flags	*flags;
	t_token	*token;
	t_cmd	*cmd;
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
int		ft_strtok(t_mini *mini, t_cmd **cmd, char *input);

//ft_expander.c
void	ft_expander(t_cmd **cmd);
char	*ft_change_dollar_x_var(t_cmd *cmd, char *command, char *var_reminder);
char	*ft_change_var(t_cmd *cmd, char *line, char **var_reminder);
char	*ft_change_name_var(char *line);
char	*ft_craft_result(char *final_line, char *line, char *var, int c);

//ft_expander_utils.c
char	*ft_strjoin_custom(char *str1, char *str2, size_t i, size_t c);
char	*ft_compare_var_name(t_cmd *cmd, char *line, char *name_var);
int		ft_var_strcmp(char *str1, char *str2);
char	*ft_add_var_value(char *str1);
char	*ft_change_line_value(char *line, char *value);

//ft_check_input.c
int		ft_check_input(t_mini **mini, char *input, char ***lines);

//ft_check_quotes.c
int		ft_check_quote(char *input, int simp_quote, int doub_quote, t_mini *mini);
int		ft_check_quote_pairs(char *input, int *i, char quote);
int		ft_locate_next_quote(int i, char *input, char quote);

//ft_check_pipes.c
int		ft_count_pipes(char *input);
char	**ft_split_pipes(char *input);
char	**ft_fill_matrix_pipes(char *input, char **splited_pipes_matrix);

//ft_check_redir.c
int		ft_check_redir_arg(char **splited_pipes_matrix, int i);
int		ft_redir_type(char *splited_arg);

//ft_check_operators.c
int		ft_is_not_mayor_n_minor_char(char c);
char	ft_type_of_operator_char(int n);
int		ft_check_special_char(char c);
int		ft_search_next_char(char *str, char c, int j);

//ft_commands.c
t_cmd	*ft_add_command(t_mini *mini, char *input);
char	*ft_get_command(t_mini *mini, char *input);
int		ft_count_args(char *input);
t_cmd	*ft_last_command(t_cmd **cmd);
char	*ft_split_var(char *line, int i, t_cmd *cmd);

//ft_check_dollar.c
int		ft_check_dollar_n_digits(char *command);
int		ft_isdigit_n_special_char(int n);
char	*ft_remove_dollar_n_digits(char *command, int i, int j);

//ft_check_home_direc.c
int		ft_check_relative_home(char *command);
char	*ft_replace_home(char *str);
char	*ft_replace_value_of_var(char *str);
char	*ft_replace_value_bis(char *str, int i, int j);

// ft_error_management.c
void	ft_many_args_error(char **argv);
void	ft_put_error(char *bash, char *file, char *error_msg);
void	ft_exit_error(char *error_msg, int exit_status);


#endif