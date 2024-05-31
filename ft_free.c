/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:27:49 by user              #+#    #+#             */
/*   Updated: 2024/05/29 09:21:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_flags_red(t_flags **flags)
{
	if (flags && *flags)
	{
		if ((*flags)->redirect)
		{
			free((*flags)->redirect->error);
			(*flags)->redirect->error = NULL;
			free((*flags)->redirect);
			(*flags)->redirect = NULL;
		}
		free(*flags);
		*flags = NULL;
	}
}

void	free_t_env(t_env **env)
{
	int i;
	
	i = 0;
	if (env && *env)
	{
		free((*env)->path);
		(*env)->path = NULL;
		if ((*env)->env)
		{
			while ((*env)->env[i])
			{
				free((*env)->env[i]);
				(*env)->env[i++] = NULL;
			}
			free((*env)->env);
			(*env)->env = NULL;
		}
		free(*env);
		*env = NULL;
	}
}

void	free_t_token(t_token **token)
{
	int i;

	i = 0;
	if (token && *token)
	{
		free((*token)->input);
		(*token)->input = NULL;
		if ((*token)->tokens)
		{
			while ((*token)->tokens[i])
			{
				free((*token)->tokens[i]);
				(*token)->tokens[i++] = NULL;
			}
			free((*token)->tokens);
			(*token)->tokens = NULL;
		}
		free(*token);
		*token = NULL;
	}
}

void	free_t_cmd(t_cmd **cmd)
{
	t_cmd	*temp;
	int 	i;
	
	i = 0;
	while (cmd && *cmd)
	{
		temp = (*cmd)->next;
		free_t_env(&((*cmd)->env));
		free_t_flags_red(&((*cmd)->flags));
		free((*cmd)->cmd);
		(*cmd)->cmd = NULL;
		if ((*cmd)->args)
		{
			while ((*cmd)->args[i])
			{
				free((*cmd)->args[i]);
				(*cmd)->args[i++] = NULL;
			}
			free((*cmd)->args);
			(*cmd)->args = NULL;
		}
		free(*cmd);
		*cmd = temp;
	}
}

void	free_t_mini(t_mini **mini)
{
	if (mini && *mini)
	{
		free_t_env(&((*mini)->env));
		free_t_flags_red(&((*mini)->flags));
		free_t_token(&((*mini)->token));
		free_t_cmd(&((*mini)->cmd));
		free(*mini);
		*mini = NULL;
	}
}
