/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 16:27:49 by user              #+#    #+#             */
/*   Updated: 2024/06/09 10:31:22 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_t_flags_red(t_flags **flags)
// {
// 	if (flags && *flags)
// 	{
// 		if ((*flags))
// 		{
// 			if ((*flags)->redirect)
// 			{
// 				if ((*flags)->redirect->error)
// 				{
// 					free((*flags)->redirect->error);
// 					(*flags)->redirect->error = NULL;
// 				}
// 				free((*flags)->redirect);
// 				(*flags)->redirect = NULL;
// 			}
// 		}
// 		// free(*flags);
// 		*flags = NULL;
// 	}
// }

// void	free_t_env(t_env **env)
// {
// 	int i;
	
// 	i = 0;
// 	if (env && *env)
// 	{
// 		if ((*env)->path)
// 		{
// 			free((*env)->path);
// 			(*env)->path = NULL;
// 		}
// 		if (&(*env)->env)
// 		{
// 			while (&(*env)->env[i])
// 			{
// 				free((*env)->env[i]);
// 				(*env)->env[i++] = NULL;
// 			}
// 		}
// 	}
// }

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

// void	free_t_cmd(t_cmd **cmd)
// {
// 	t_cmd	*temp;
// 	int		i;
	
// 	while (cmd && *cmd)
// 	{
// 		temp = (*cmd)->next;
// 		if ((*cmd)->env)
// 			free_t_env(&((*cmd)->env));
// 		if ((*cmd)->flags)
// 			free_t_flags_red(&((*cmd)->flags));
// 		if ((*cmd)->cmd)
// 		{
// 			free((*cmd)->cmd);
// 			(*cmd)->cmd = NULL;
// 		}
// 		if ((*cmd)->args)
// 		{
// 			i = 0;
// 			while ((*cmd)->args[i])
// 			{
// 				free((*cmd)->args[i]);
// 				(*cmd)->args[i++] = NULL;
// 			}
// 			free((*cmd)->args);
// 			(*cmd)->args = NULL;
// 		}
// 		free(*cmd);
// 		*cmd = temp;
// 	}
// }

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


void	free_t_env(t_env *env)
{
	if (env == NULL)
		return;
	if (env->path != NULL)
	{
		free(env->path);
		env->path = NULL;
	}
	if (env->env != NULL)
	{
		int i = 0;
		while (env->env[i])
		{
			free(env->env[i]);
			env->env[i++] = NULL;
		}
		free(env->env);
		env->env = NULL;
	}
	free(env);
}

void	free_t_flags_red(t_flags *flags)
{
	if (flags == NULL)
		return;
	if (flags->redirect != NULL)
	{
		if (flags->redirect->error != NULL)
		{
			free(flags->redirect->error);
			flags->redirect->error = NULL;
		}
		free(flags->redirect);
		flags->redirect = NULL;
	}
	free(flags);
}

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

	if (mini->flags != NULL)
	{
		if (mini->flags->redirect != NULL)
		{
			free(mini->flags->redirect);
			mini->flags->redirect = NULL;
		}
		free(mini->flags);
		mini->flags = NULL;
	}

	if (mini->token != NULL)
	{
		if (mini->token->input != NULL)
		{
			free(mini->token->input);
			mini->token->input = NULL;
		}
		if (mini->token->tokens != NULL)
		{
			int i = 0;
			while (mini->token->tokens[i])
			{
				free(mini->token->tokens[i]);
				mini->token->tokens[i++] = NULL;
			}
			free(mini->token->tokens);
			mini->token->tokens = NULL;
		}
		free(mini->token);
		mini->token = NULL;
	}

	t_cmd *current_cmd;
	t_cmd *next_cmd;
	current_cmd = mini->cmd;
	while (current_cmd != NULL)
	{
		next_cmd = current_cmd->next;
		if (current_cmd->env != NULL)
		{
			free_t_env(current_cmd->env);
			current_cmd->env = NULL;
		}
		if (current_cmd->flags != NULL)
		{
			// free_t_flags_red(current_cmd->flags);
			current_cmd->flags = NULL;
		}
		if (current_cmd->cmd != NULL)
		{
			free(current_cmd->cmd);
			current_cmd->cmd = NULL;
		}
		if (current_cmd->args != NULL)
		{
			int i = 0;
			int	j = 0;
			printf("%s\n", current_cmd->args[0]);
			while (current_cmd->args[i])
				i++;
			printf("%d\n", i);
			while (j != i)
				free(current_cmd->args[j++]);
			free(current_cmd->args);
			current_cmd->args = NULL;
		}
		free(current_cmd);
		current_cmd = next_cmd;
	}
	free(mini);
}
