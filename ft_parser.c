/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/21 13:05:16 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_create_path(char **env)
{
	char	**path;
	int		i;

	i = -1;
	path = NULL;
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			path = ft_split(env[i] + 5, ':');
	}
	return (path);
}

char	*ft_validate_comm(char *cmd, char **path)
{
	char	*command;
	char	*test;
	int		j;

	j = 0;
	if (access(cmd, X_OK) == 0 && ft_strrchr(cmd, '/'))
		return (cmd);
	if (access(cmd, X_OK) != 0 && ft_strrchr(cmd, '/'))
		return (NULL); // Error 127
	command = ft_strjoin("/", cmd);
	while (path[j] != NULL)
	{
		test = ft_strjoin(path[j++], command);
		if (access(test, X_OK) == 0)
		{
			free(command);
			return (test);
		}
		free(test);
	}
	free(command);
	// Error 127
	return (NULL);
}

char **ft_strstr_dup(char **str)
{
	int	i;

	i = 0;
    if (str == NULL)
        return NULL;
    char **dup = (char **)ft_calloc(sizeof(char *), ft_strstr_len(str) + 1);
    if (dup == NULL)
        return (NULL);
    while (i < ft_strstr_len(str))
	{
        dup[i] = ft_strdup(str[i]);
        if (dup[i] == NULL)
		{
            ft_strstr_free(dup);
            return NULL;
        }
		i++;
    }
    return dup;
}

int process_lines(t_cmd **cmd, t_mini *mini, char **lines)
{
	t_cmd	*new_cmd;
	t_cmd	*current;
	int		i;

	i = 0;
	while (lines && lines[i] != NULL)
	{
		new_cmd = ft_add_command(lines[i], -1);
		if (*cmd == NULL)
			*cmd = new_cmd;
		else
		{
			current = *cmd;
			while (current->next != NULL)
				current = current->next;
			current->next = new_cmd;
		}
		new_cmd->files = ft_calloc(sizeof(t_files), 1);
		new_cmd->files->error = 0;
		ft_files(new_cmd, mini, new_cmd->files);
		if (new_cmd->files->error == -1)
			return (-1);
		free(lines[i++]);
	}
	if (lines != NULL)
		free(lines);
	return (0);
}

char	*ft_route_cmd(char **env, char *tmp)
{
	char	**path;
	char	*cmd;

	path = ft_create_path(env); // Poner el PATH en la estructura y en el caso de que no exista, cogerlo del ejecutable env
	cmd = ft_validate_comm(tmp, path);
	if (cmd == NULL)
	{
		printf("Ese comando no existe, prueba otro\n");
		ft_strstr_free(path);
		return (NULL);	// Error 127 Crear outfiles antes de salir e imprimir
					// "printf("mini: command not found");
					// si infiles y outfiles no dan error.
	}
	ft_strstr_free(path);
	return (cmd);
}

void	ft_remove_files(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*current;
	char	**tmp;
	int		size;
	int		i;
	int		j;

	current = cmd;
	while (current != NULL)
	{
		i = -1;
		j = 0;
		size = 0;
		tmp = ft_strstr_dup(current->args);
		ft_strstr_free(current->args);
		while (tmp[++i])
		{
			if (ft_type(tmp[i]) != 0)
				i++;
			else
				size++;
		}
		printf(B_OR_0"SIZE --> %d\n"RESET, size);
		current->args = (char **)ft_calloc(sizeof(char *), size + 1);
		i = -1;
		j = 0;
		while (tmp[++i])
		{
			if (ft_type(tmp[i]) != 0)
				i++;
			else
			{
				if (j == 0)
				{
					current->cmd = ft_route_cmd(mini->env->env, tmp[i]);
					if (current->cmd == NULL)
						mini->cmd->files->error = -1;
				}
				current->args[j++] = ft_strdup(tmp[i]);
			}
		}
		ft_strstr_free(tmp);
		tmp = NULL;
		current = current->next;
	}
}

// void	ft_select_files(t_cmd *cmd ,t_mini *mini)
// {
	
// }

int	ft_strtok(t_mini *mini, t_cmd **cmd, char *input)
{
	char	**lines;

	lines = ft_check_input(mini, input);
	if (mini->flags->pipe == -1 || mini->flags->quote == -1 || mini->flags->locate_red == -1)
		return (0);
	else if (mini->flags->pipe == 0)
	{
		*(cmd) = ft_add_command(input, -1);
		(*cmd)->files = ft_calloc(sizeof(t_files), 1);
		(*cmd)->files->error = 0;
		if (mini->flags->redirect && mini->flags->redirect->number != 0)
			ft_files(*(cmd), mini, (*cmd)->files);
		if ((*cmd)->files->error == -1)
			return (0);
	}
	else
	{
		if (process_lines(cmd, mini, lines) == -1)
		{
			ft_strstr_free(lines);
			return (0);
		}
	}
	ft_remove_files(*cmd, mini);
	if (mini->cmd->files->error == -1)
		return (0);
	// ft_select_files(*cmd, mini);
	print_cmd(*cmd);

	// free((*cmd)->files);
	// print_files((*cmd)->files);

	return (1);
}
