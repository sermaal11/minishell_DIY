/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:27:49 by user              #+#    #+#             */
/*   Updated: 2024/06/27 08:45:37 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_t_env(t_env **env)
{
	int i;
	
	i = 0;
	if (env && *env)
	{
		if ((*env)->path)
			free((*env)->path);
		if (&(*env)->env)
		{
			while (&(*env)->env[i])
				free((*env)->env[i++]);
		}
	}
	free(*env);
}

// void	free_t_token(t_token **token)
// {
// 	int i;

// 	i = 0;
// 	if (token && *token)
// 	{
// 		free((*token)->input);
// 		(*token)->input = NULL;
// 		if ((*token)->tokens)
// 		{
// 			while ((*token)->tokens[i])
// 			{
// 				free((*token)->tokens[i]);
// 				(*token)->tokens[i++] = NULL;
// 			}
// 			free((*token)->tokens);
// 			(*token)->tokens = NULL;
// 		}
// 		free(*token);
// 		*token = NULL;
// 	}
// }

void	free_t_cmd(t_cmd **cmd)
{
	t_cmd	*temp;
	int		i;
	
	while (cmd && *cmd)
	{
		i = 0;
		temp = (*cmd)->next;
		if ((*cmd)->cmd)
			free((*cmd)->cmd);
		if ((*cmd)->args)
		{
			while ((*cmd)->args[i])
				free((*cmd)->args[i++]);
			free((*cmd)->args);
		}
		free(*cmd);
		*cmd = temp;
	}
}

// void	free_t_mini(t_mini **mini)
// {
// 	if (mini && *mini)
// 	{
// 		if ((*mini)->env)
// 			free_t_env(&(*mini)->env);
// 		// if ((*mini)->flags)
// 		// 	free_t_flags_red(&(*mini)->flags);
// 		if ((*mini)->token)
// 			free_t_token(&(*mini)->token);
// 		if ((*mini)->cmd)
// 			free_t_cmd(&((*mini)->cmd));
// 		if ((*mini)->flags)
// 			free((*mini)->flags);
// 		free(*mini);
// 		*mini = NULL;
// 	}
// }



void free_t_mini(t_mini *mini)
{
	if (mini == NULL)
		return;
	if (mini->env != NULL) 
	{
		if (mini->env->path != NULL)
		{
			free(mini->env->path);
			mini->env->path = NULL;
		}
		if (mini->env->env != NULL)
		{
			int i = 0;
			while (mini->env->env[i])
			{
				free(mini->env->env[i]);
				mini->env->env[i++] = NULL;
			}
			free(mini->env->env);
			mini->env->env = NULL;
		}
	}

	if (mini->flags)
		free(mini->flags);
	if (mini->token != NULL)
	{
		if (mini->token->input != NULL)
			free(mini->token->input);
		if (mini->token->tokens != NULL)
		{
			int i = 0;
			while (mini->token->tokens[i])
				free(mini->token->tokens[i++]);
			free(mini->token->tokens);
		}
		free(mini->token);
	}
	if (mini->env)
		free(mini->env);
	free(mini);
}
