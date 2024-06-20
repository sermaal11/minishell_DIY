/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: descamil <descamil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 13:20:46 by descamil          #+#    #+#             */
/*   Updated: 2024/06/20 17:37:19 by descamil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **ft_tript(char *str, int size, int start)
{
	int     i = -1;
	int     j = 0;
	char    **div;

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
	if (str[i] == '$')
		return(++i);
	if (ft_isdigit(str[i]) == 1)
	{
		printf(B_CY_2"%c\n"RESET, str[i]);
		while (ft_isdigit(str[i]) == 1)
			i++;
		printf(B_YE_2"%d\n"RESET, i);
		return (i);
	}
	while (ft_isalnum(str[i]) == 1 && str[i] != '\0')
		i++;
	return(i);
}

int main(int argc, char **argv, char **env)
{
	char    *str = "$USER";
	char    **div = NULL;
	char	*tmp = NULL; 
	char	*div_tmp = NULL;
	int		point = 0;
	int		iter = -1;

	if (argc != 1)
		printf("%s\n", argv[1]);

	while (ft_strchr(str + point, '$') - str >= 0)
	{
		if (iter == -1)
			iter = (iter * -1) - 1;
		if (div_tmp && ft_strchr(div_tmp, '$') == NULL)
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
		div = ft_tript(str, ft_size_var(ft_strchr(str + point, '$')), ft_strchr(str + point, '$') - str);
		div[1] = ft_dolar_to_iqual(div[1]);
		tmp = ft_change_var(div[1], env);
		div_tmp = ft_join(div, tmp);
		if (ft_strlen(tmp) != 0 || ft_strlen(div_tmp) == 0 || ft_strncmp(div[1], "$=", 2) == 0 || ft_isdigit(div[1][1]) == 1)
			point = (ft_strchr(str + point, '$') - str + 1);
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
		iter++;
	}
	if (str && iter != 1)
		free(str);
	// printf(B_WH_0"\nCADENA RESULTANTE -->\t\"%s\"\n\n"RESET, div_tmp);
	if (div_tmp)
		free(div_tmp);
	return (0);
}
