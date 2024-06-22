/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/06/22 09:33:37 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr_mod(const char *str, int value, int stop)
{
	while (*str)
	{
		if (*str == (char)value && stop-- == 0)
			return ((char *)str);
		str++;
	}
	if (*str == (char)value)
		return ((char *)str);
	return (NULL);
}

char    **ft_tript(char *str, int size, int start)
{
	int     i = -1;
	int     j = 0;
	int 	exp = 0;
	char    **div;

	if (size == -1)
	{
		exp = 1;
		size = 1;
	}
	div = (char **)ft_calloc(sizeof(char *),  4);
	if (start != 0)
	{
		div[0] = ft_calloc(sizeof(char), start + 1);
		while (++i < start)
			div[0][i] = str[i];
	}
	else
		div[++i] = NULL;
	div[1] = ft_calloc(sizeof(char),  size + 1);
	while (j < size)
		div[1][j++] = str[i++];
	if ((int)ft_strlen(str) > size + start)
	{
		div[2] = ft_calloc(sizeof(char), (ft_strlen(str) - start + size + 1));
		j = 0;
		while (str[i] != '\0')
			div[2][j++] = str[i++];
	}
	else
		div[2] = NULL;
	return (div);
}

char *ft_change_var(char *div, char **env)
{
    int     i = 0;
    char    *str;
	char	*glob;
    
	if (div && ft_strlen(div) == 1 && ft_strncmp(div, "$", 1) == 0)
	{
		str = malloc(sizeof(char) * 2);
		ft_memset(str, '$', 1);
		str[1] = '\0';
		return (str);
	}
	if (div && ft_strlen(div) == 2 && ft_strncmp(div, "?=", 2) == 0)
	{
		glob = ft_itoa(127);
		// g_exit_status // GESTIONAR LA VRIABLE SUSTITUYENDO 127 POR LA GLOBAL
		str = malloc(sizeof(char) * ft_strlen(glob) + 1);
		ft_memcpy(str, glob, ft_strlen(glob) + 1);
		free(glob);
		return (str);
	}
    while (env[i] != NULL)
    {
        if (ft_strnstr(env[i], div, ft_strlen(div)) != NULL)
        {
			str = malloc(sizeof(char) * ft_strlen(env[i]) - ft_strlen(div) + 1);
            ft_memcpy(str, env[i] + ft_strlen(div),ft_strlen(env[i]) - ft_strlen(div) + 1);
            if (str != NULL)
                return (str);
        }
        i++;
    }
    return ("");
}

char	*ft_dolar_to_iqual(char *div)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	if (ft_strncmp(div, "$", 1) == 0 && ft_strlen(div) == 1)
		return (div);
	while (div[j] != '\0')
		div[i++] = div[j++];
	if (div[j] == '\0')
		div[i] = '=';
	return (div);
}

char	*ft_join(char **div, char *tmp)
{
	char	*ptr = NULL;
	char	*final = NULL;
	
	if (div[0] == NULL && div[2] == NULL)
	{
		final = ft_calloc(sizeof(char), ft_strlen(tmp) + 1);
		ft_strlcpy(final, tmp, ft_strlen(tmp) + 1);
	}
	else if (div[0] != NULL && div[2] == NULL)
		final = ft_strjoin(div[0], tmp);
	else if (div[2] != NULL && div[0] == NULL)
		final = ft_strjoin(tmp, div[2]);
	else
	{
		if (div != NULL)
			ptr = ft_strjoin(div[0], tmp);
		if (ptr != NULL)
		{
			final = ft_strjoin(ptr, div[2]);
			free(ptr);
		}
	}
	if (final)
		return (final);
	return (tmp);
}

int	ft_size_var(char *str)
{
	int	i;
	
	i = 1;
	if (str[i] == '$' || str[i] == '?')
		return(++i);
	if (str[i] == ' ' || str[i] == '\0')
		return (-1);
	if (ft_isdigit(str[i]) == 1)
	{
		while (str[i] != ' ' && str[i] != '$' && str[i] != '\0')
			i++;
		return (i);
	}
	while (ft_isalnum(str[i]) == 1 && str[i] != '\0')
		i++;
	return(i);
}

void	ft_ex_free(char **div, char *tmp)
{
	if (div)
	{
		free(div[0]);
		if (div[1])
			free(div[1]);
		free(div[2]);
		free(div);
	}
	if (tmp && ft_strlen(tmp) != 0)
		free(tmp);
}

int main(int argc, char **argv, char **env)
{
	char	*str = "$USER";
	char	**div = NULL;
	char	*tmp = NULL; 
	char	*div_tmp = NULL;
	int		iter = -1;
	int		stop = 0;
	char	*res;
	
	if (argc != 1)
		printf("%s\n", argv[1]);
	while (ft_strchr_mod(str, '$', stop) - str >= 0)
	{
		if (iter == -1)
			iter = 0;
		if (div_tmp && ft_strchr_mod(div_tmp, '$', stop) == NULL)
			break ;
		if (div_tmp != NULL)
		{
			if (str != NULL && iter != 1)
			{
				free(str);
				str = NULL;
			}
			str = ft_calloc(sizeof(char), ft_strlen(div_tmp) + 1);
			ft_strlcpy(str, div_tmp, ft_strlen(div_tmp) + 1);
			free(div_tmp);
		}
		res = ft_strchr_mod(str, '$', stop);
		div = ft_tript(str, ft_size_var(res), res - str);
		div[1] = ft_dolar_to_iqual(div[1]);
		tmp = ft_change_var(div[1], env);
		if (ft_strlen(tmp) == 1 && ft_strncmp(tmp, "$", 1) == 0)
			stop += 1;
		div_tmp = ft_join(div, tmp);
		ft_ex_free(div, tmp);
		iter++;
	}
	if (str && iter != 1)
		free(str);
	printf(B_WH_0"\nCADENA RESULTANTE -->\t\"%s\"\n\n"RESET, div_tmp);
	if (div_tmp)
		free(div_tmp);
	return (0);
}
